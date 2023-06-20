#pragma once

#include <standard_libs.h>

class Config
{
    public:
        Config(std::string_view file_stream = {"config.cfg"})
        {
            load_default_setting();

            std::fstream config_file(file_stream.data());

            if (!config_file.is_open())
            {
                std::cout << "[WARNING]: Could not read configuration file ! Creating a new ..." << std::endl;

                config_file.open(file_stream.data(), std::fstream::in | std::fstream::out | std::fstream::trunc);

                if (!config_file.is_open())
                    throw "[ERROR]: Unable to create settings file ! Leaving the program ...";

                write_cfg_template(config_file);

                std::cout << "[INFO]: Configuration file created !" << std::endl;
            }
            else
                read_config(config_file);

            config_file.close();
        }

        std::string hostname;
        std::string port;

    private:
        void load_default_setting()
        {
            hostname = "localhost";
            port = "4444";
        }

        void write_cfg_template(std::fstream &cfg_file)
        {
            cfg_file << "Hostname = " << hostname << "\n";
            cfg_file << "Port = " << port << "\n";
        }

        void read_config(std::fstream &cfg_file)
        {
            std::string file_line;
            std::string line_content;

            std::stringstream str_stream;

            while (std::getline(cfg_file, file_line))
            {
                str_stream.clear();
                str_stream.str(file_line);

                str_stream >> line_content;

                if (line_content == "Hostname")
                {
                    try
                    {
                        hostname = read_value(str_stream, line_content);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else if (line_content == "Port")
                {
                    try
                    {
                        port = read_value(str_stream, line_content);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
            }
        }

        std::string read_value(std::stringstream &str_stream, std::string option)
        {
            std::string line_content;
            str_stream >> line_content;

            if (line_content == "=")
            {
                str_stream >> line_content;
                return line_content.c_str();
            }
            else
            {
                std::string ex = "[WARNING]: Could not load " + option + " configuration ! The default configuration will be kept.\n";
                throw std::invalid_argument(ex);
            }
        }
};