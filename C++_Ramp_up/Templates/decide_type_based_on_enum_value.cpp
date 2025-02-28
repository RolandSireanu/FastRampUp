enum Sections
    {
        DNSHeader_id,
        DNSHeader_flags,
        DNSHeader_qdcount,
        DNSHeader_ancount,
        DNSHeader_nscount,
        DNSHeader_arcount,
        DNSQuestion_qname,
        DNSQuestion_qtype,
        DNSQuestion_qclass,
        DNSReply_name,
        DNSReply_type,
        DNSReply_classType,
        DNSReply_ttl,
        DNSReply_length,
        DNSReply_data
    };

template <Sections Value>
concept IsTwoBytesSection =       (Value == Sections::DNSHeader_id) || 
                            (Value == Sections::DNSHeader_flags) ||
                            (Value == Sections::DNSHeader_qdcount) ||
                            (Value == Sections::DNSHeader_ancount) ||
                            (Value == Sections::DNSHeader_nscount) ||
                            (Value == Sections::DNSHeader_arcount) ||
                            (Value == Sections::DNSQuestion_qtype) ||
                            (Value == Sections::DNSQuestion_qclass) ||
                            (Value == Sections::DNSReply_type) ||
                            (Value == Sections::DNSReply_classType) ||
                            (Value == Sections::DNSReply_length);


template<Sections Value>
concept IsFourBytesSection = (Value == DNSReply_ttl) ||
                               (Value == DNSReply_data);

template<Sections S>
struct ReturnType
{
    using type = std::conditional_t<IsTwoBytesSection<S>, uint16_t, 
                 std::conditional_t<IsFourBytesSection<S>, uint32_t, std::string>>;
};
