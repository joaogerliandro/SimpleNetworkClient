#pragma once

#include <standard_libs.h>
#include <common.h>
#include <enum.h>

using namespace nlohmann;

class Message
{
    public:
        Message(std::string message_str)
        {
            json message_json = json::parse(message_str);

            m_sender_ipaddress = message_json["SenderIpAddress"];
            m_sender_portnumber = message_json["SenderPortNumber"];
            m_content = message_json["Content"];
            m_message_type = message_json["MessageType"];
        }

        Message(std::string sender_ipaddress, std::uint32_t sender_portnumber, std::string content, MESSAGE_TYPE message_type) :
            m_sender_ipaddress(sender_ipaddress),
            m_sender_portnumber(sender_portnumber),
            m_content(content),
            m_message_type(message_type)
        {}

        std::string to_string()
        {
            json message_json = {
                {"SenderIpAddress", m_sender_ipaddress},
                {"SenderPortNumber", m_sender_portnumber},
                {"Content", m_content},
                {"MessageType", m_message_type}
            };

            return message_json.dump();
        }

        std::string m_sender_ipaddress;
        std::uint32_t m_sender_portnumber;
        std::string m_content;
        MESSAGE_TYPE m_message_type;

        // date_time m_send_datetime
};
