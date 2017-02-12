#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <unordered_map>

namespace qh
{
    class INIParser
    {
    public:
        typedef std::unordered_map<std::string, std::string> key_value_t;
        typedef std::string section_name_t;

        INIParser();
        ~INIParser();

        //! \brief ����һ�������ϵ�INI�ļ�
        //! \param[in] - const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief ����һ������INI��ʽ���ڴ����ݡ�
        //!   ���磺ini_data="a:1||b:2||c:3"
        //!         ����<code>Parse(ini_data, ini_data_len, "||", ":")</code>���ɽ�����������ݡ�
        //!         �������֮��
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
        //! \return - bool
        bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");


        //! \brief ��Ĭ��section�в���ĳ��key���������ҵ���value������Ҳ���������һ���մ�
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - ���������true�����ҵ����key
        //! \return - const std::string& - ���صľ���key��Ӧ��value
        const std::string& Get(const std::string& key, bool* found);

        const std::string& Get(const std::string& section, const std::string& key, bool* found);

    private:
        //! \brief ����һ��section
        //! \param[in] - const std::string & section
        //! \param[in] - const std::string& line_seperator
        //! \param[in] - const std::string& key_value_seperator
        //! \return - bool
        bool ParseSection(const std::string& section, const std::string& line_seperator, const std::string& key_value_seperator);

        //! \brief ����һ��key value
        //! \param[in] - const section_name_t& section_name
        //! \param[in] - const std::string & key_value
        //! \param[in] - const std::string& key_value_seperator
        //! \return - bool
        bool ParseKeyValue(const section_name_t& section_name, const std::string& key_value, const std::string& key_value_seperator);

    private:
        std::unordered_map<section_name_t, key_value_t> section_key_value;
    };
}

#endif

