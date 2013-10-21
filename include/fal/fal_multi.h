
#ifndef _FAL_MULTI_H_
#define _FAL_MULTI_H_

/*supports 32 entries*/
#define FAL_IGMP_SG_ENTRY_MAX 32

typedef enum
{
    FAL_ADDR_IPV4 = 0,
    FAL_ADDR_IPV6
} fal_addr_type_t;

typedef struct
{
    fal_addr_type_t type;
    union
    {
        fal_ip4_addr_t ip4_addr;
        fal_ip6_addr_t ip6_addr;
    } u;
} fal_igmp_sg_addr_t;

typedef struct
{
    fal_igmp_sg_addr_t source;
    fal_igmp_sg_addr_t group;
    fal_pbmp_t port_map;
} fal_igmp_sg_entry_t;

//#define MULTI_DEBUG_
#ifdef MULTI_DEBUG_
#define MULTI_DEBUG(x...) aos_printk(x)
#else
#define MULTI_DEBUG(x...)
#endif

#define FAL_ACL_LIST_MULTICAST 55
#define FAL_MULTICAST_PRI   5

#define MULT_ACTION_SET      0
#define MULT_ACTION_CLEAR    1

// static a_uint32_t rule_nr=1;

typedef struct
{
    a_uint8_t index; //MAX is 32
    fal_igmp_sg_entry_t entry; //Stores the specific ACL rule info
} multi_acl_info_t;


#endif
