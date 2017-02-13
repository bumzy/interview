#include "ini_parser.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "tokener.h"

namespace qh
{
    INIParser::INIParser()
        : section_key_value()
    {
    }

    INIParser::~INIParser()
    {
    }

    bool INIParser::Parse(const std::string& ini_file_path)
    {
        std::ifstream ini_file(ini_file_path);
        std::stringstream ini_data_buffer;
        if(ini_file.is_open())
        {
            ini_data_buffer << ini_file.rdbuf();
            ini_file.close();
        }
        else
            return false;

        return Parse(ini_data_buffer.str().c_str(), ini_data_buffer.str().length());
    }

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
    {
        section_key_value.clear();
        if(line_seperator.empty())
        {
            fprintf(stderr, "ERROR : line_seperator is empty\n");
            return false;
        }
        if(key_value_seperator.empty())
        {
            fprintf(stderr, "ERROR : key_value_seperator is empty\n");
            return false;
        }
        if(line_seperator == key_value_seperator)
        {
            fprintf(stderr, "ERROR : line_seperator is same with key_value_seperator\n");
            return false;
        }
        if(line_seperator.find("[") != std::string::npos || line_seperator.find("]") != std::string::npos)
        {
            fprintf(stderr, "ERROR : line_seperator must't include '[' or ']'\n");
            return false;
        }
        if(key_value_seperator.find("[") != std::string::npos || key_value_seperator.find("]") != std::string::npos)
        {
            fprintf(stderr, "ERROR : key_value_seperator must't include '[' or ']'\n");
            return false;
        }

        if(ini_data == NULL || ini_data[0] == '\0' || ini_data_len == 0)
            return true;

        Tokener token(ini_data, ini_data_len);

        const char* startpos = token.getCurReadPos();
        const char* curpos = startpos;
        int nreadable = token.getReadableSize();
        std::string section = token.nextString('[');

        if(section.empty() && curpos == token.getCurReadPos())
        {
            section = std::string(ini_data, ini_data_len);
            return ParseSection(section, line_seperator, key_value_seperator);
        }

        while(!token.isEnd())
        {
            if(curpos == token.getCurReadPos())
            {
                section.assign(curpos - 1, nreadable + 1);
                return ParseSection(section, line_seperator, key_value_seperator);
            }
            else
            {
                if(!section.empty())
                {
                    if(curpos > startpos && *(curpos - 1) == '[')
                        section = std::string("[") + section;
                    if(!ParseSection(section, line_seperator, key_value_seperator))
                    {
                        return false;
                    }
                }
                curpos = token.getCurReadPos();
                nreadable = token.getReadableSize();
                section = token.nextString('[');
            }
        }
        return true;
    }

    bool INIParser::ParseSection(const std::string& section, const std::string& line_seperator, const std::string& key_value_seperator)
    {
        Tokener token(section);
        section_name_t section_name;
        if(token.current() == '[')
        {
            token.next();
            const char* curpos = token.getCurReadPos();
            section_name = token.nextString(']');
            if(curpos == token.getCurReadPos())
            {
                fprintf(stderr, "ERROR : key is empty\n");
                return false;
            }
        }
        while(!token.isEnd())
        {
            const char* curpos = token.getCurReadPos();
            int nreadable = token.getReadableSize();
            std::string key_value = token.nextString(line_seperator);

            if(!token.isEnd() && curpos == token.getCurReadPos())
            {
                key_value.assign(curpos, nreadable);
                return ParseKeyValue(section_name, key_value, key_value_seperator);
            }
            else if(!key_value.empty())
            {
                if(!ParseKeyValue(section_name, key_value, key_value_seperator))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool INIParser::ParseKeyValue(const section_name_t& section_name, const std::string& key_value, const std::string& key_value_seperator)
    {
        if(key_value.empty())
        {
            return true;
        }

        size_t pos = key_value.find(key_value_seperator);
        if(pos == std::string::npos)
        {
            fprintf(stderr, "ERROR : key_value[%s] does not include key_value_seperator[%s]\n", key_value.c_str(), key_value_seperator.c_str());
            return false;
        }
        if(key_value.find(key_value_seperator, pos + key_value_seperator.length()) != std::string::npos)
        {
            fprintf(stderr, "ERROR : key_value[%s] has more than one key_value_seperator[%s]\n", key_value.c_str(), key_value_seperator.c_str());
            return false;
        }

        Tokener token(key_value);
        std::string key = token.nextString(key_value_seperator);

        if(key.empty())
        {
            fprintf(stderr, "ERROR : key is empty\n");
            return false;
        }

        const char* curpos = token.getCurReadPos();
        int nreadable = token.getReadableSize();
        std::string value = std::string(curpos, nreadable);

        section_key_value[section_name][key] = value;
        return true;
    }

    const std::string& INIParser::Get(const std::string& key, bool* found)
    {
        return Get("", key, found);
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
    {
        static const std::string empty("");

        if(section_key_value.find(section) != section_key_value.end() &&
            section_key_value[section].find(key) != section_key_value[section].end())
        {
            if(found != NULL)
                *found = true;
            return section_key_value[section][key];
        }

        if(section_key_value[""].find(key) != section_key_value[""].end())
        {
            if(found != NULL)
                *found = true;
            return section_key_value[""][key];
        }

        if(found != NULL)
            *found = false;
        return empty;
    }
}
