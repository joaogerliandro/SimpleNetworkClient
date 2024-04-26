#pragma once

#include <standard_libs.h>

class Room
{
    public:
        Room(uint8_t room_id, uint8_t room_size, uint8_t connected_clients, std::string room_name) : m_id(room_id), m_size(room_size), m_connected_clients(connected_clients) , m_name(room_name) {}

        inline uint8_t get_id() { return m_id; }

        inline uint8_t get_size() { return m_size; }

        inline uint8_t get_connected_clients() { return m_connected_clients; }

        inline std::string get_name() { return m_name; }

    private:
        uint8_t m_id;
        uint8_t m_size;
        uint8_t m_connected_clients;
        std::string m_name;
};
