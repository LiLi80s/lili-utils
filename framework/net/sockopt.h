#include <netinet/tcp.h>



/* for TCP_xxx defines */
union val {
  int    i_val;
  long   l_val;
  struct linger linger_val;
  struct timeval timeval_val;
} val;



static char *sock_str_flag(union val *, int);
static char *sock_str_int(union val *, int);
static char *sock_str_linger(union val *, int);
static char *sock_str_timeval(union val *, int);




struct sock_opts {
  const char       *opt_str;
  int
  int
  char
} sock_opts[] = {
    { "SO_BROADCAST",      SOL_SOCKET     ,    SO_BROADCAST       ,   sock_str_flag     },  
    { "SO_DEBUG",          SOL_SOCKET     ,    SO_DEBUG           ,   sock_str_flag     },             
    { "SO_DONTROUTE",      SOL_SOCKET     ,    SO_DONTROUTE       ,   sock_str_flag     },            
    { "SO_ERROR",          SOL_SOCKET     ,    SO_ERROR           ,   sock_str_int      },            
    { "SO_KEEPALIVE",      SOL_SOCKET     ,    SO_KEEPALIVE       ,   sock_str_flag     },         
    { "SO_LINGER",         SOL_SOCKET     ,    SO_LINGER          ,   sock_str_linger   },            
    { "SO_OOBINLINE",      SOL_SOCKET     ,    SO_OOBINLINE       ,   sock_str_flag     },         
    { "SO_RCVBUF",         SOL_SOCKET     ,    SO_RCVBUF          ,   sock_str_int      },        
    { "SO_SNDBUF",         SOL_SOCKET     ,    SO_SNDBUF          ,   sock_str_int      },      
    { "SO_RCVLOWAT",       SOL_SOCKET     ,    SO_RCVLOWAT        ,   sock_str_int      },      
    { "SO_SNDLOWAT",       SOL_SOCKET     ,    SO_SNDLOWAT        ,   sock_str_int      },      
    { "SO_RCVTIMEO",       SOL_SOCKET     ,    SO_RCVTIMEO        ,   sock_str_timeval  },     
    { "SO_SNDTIMEO",       SOL_SOCKET     ,    SO_SNDTIMEO        ,   sock_str_timeval  },    
    { "SO_REUSEADDR",      SOL_SOCKET     ,    SO_REUSEADDR       ,   sock_str_flag     },   
#ifdef SO_REUSEPORT
    { "SO_REUSEPORT",      SOL_SOCKET     ,    SO_REUSEPORT       ,   sock_str_flag     },   
#else
    { "SO_REUSEPORT",      0              ,    0                  ,   NULL              },  
#endif
    { "SO_TYPE",           SOL_SOCKET     ,    SO_TYPE            ,   sock_str_int      },
    { "SO_USELOOPBACK",    SOL_SOCKET     ,    SO_USELOOPBACK     ,   sock_str_flag     }, 
    { "IP_TOS",            IPPROTO_IP     ,    IP_TOS             ,   sock_str_int      },     
    { "IP_TTL",            IPPROTO_IP     ,    IP_TTL             ,   sock_str_int      },      
    { "IPV6_DONTFRAG",     IPPROTO_IPV6   ,    IPV6_DONTFRAG      ,   sock_str_flag     },      
    { "IPV6_UNICAST_HOPS", IPPROTO_IPV6   ,    IPV6_UNICAST_HOPS  ,   sock_str_int      }, 
    { "IPV6_V6ONLY",       IPPROTO_IPV6   ,    IPV6_V6ONLY        ,   sock_str_flag     },    
    { "TCP_MAXSEG",        IPPROTO_TCP    ,    TCP_MAXSEG         ,   sock_str_int      },  
    { "TCP_NODELAY",       IPPROTO_TCP    ,    TCP_NODELAY        ,   sock_str_flag     },
    { "SCTP_AUTOCLOSE",    IPPROTO_SCTP   ,    SCTP_AUTOCLOSE     ,   sock_str_int      },    
    { "SCTP_MAXBURST",     IPPROTO_SCTP   ,    SCTP_MAXBURST      ,   sock_str_int      },  
    { "SCTP_MAXSEG",       IPPROTO_SCTP   ,    SCTP_MAXSEG        ,   sock_str_int      },  
    { "SCTP_NODELAY",      IPPROTO_SCTP   ,    SCTP_NODELAY       ,   sock_str_flag     },      
    { NULL,                0              ,    0                  ,   NULL              },    
};
