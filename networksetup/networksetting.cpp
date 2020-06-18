#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()

#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_RAW, INET_ADDRSTRLEN
#include <netinet/ip.h>       // IP_MAXPACKET (which is 65535)
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_ARP = 0x0806
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>
#include <ctype.h>
#include <errno.h>            // errno, perror()

#include <netinet/in.h>
#include <net/route.h>    

#include <ifaddrs.h>





int g_success_num=0;


 /**
    * Create socket function
    */
int create_socket() {

  int sockfd = 0;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1){
    fprintf(stderr, "Could not get socket.\n");
    return -1;
  }

  return sockfd;

}

/**
* Generic ioctrlcall to reduce code size
*/
int generic_ioctrlcall(int sockfd, u_long *flags, struct ifreq *ifr) {

  if (ioctl(sockfd, (long unsigned int)flags, &ifr) < 0) {
    fprintf(stderr, "ioctl: %s\n", (char *)flags);
    return -1;
  }
  return 1;
}

/**
* Set route with metric 100
*/
int set_route(int sockfd, char *gateway_addr,  struct sockaddr_in *addr,char *subnet_mask,char * iface_name) {
  struct rtentry route;
  int err = 0;
  memset(&route, 0, sizeof(route));
  addr = (struct sockaddr_in*) &route.rt_gateway;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr(gateway_addr);
  addr = (struct sockaddr_in*) &route.rt_dst;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr =INADDR_ANY; //inet_addr(gateway_addr) & inet_addr(subnet_mask);
  addr = (struct sockaddr_in*) &route.rt_genmask;
  addr->sin_family = AF_INET;

  addr->sin_addr.s_addr = inet_addr(subnet_mask);
  route.rt_flags = RTF_UP | RTF_GATEWAY;
  route.rt_metric = 600;//means ttl?
  //route.rt_dev = iface_name;
  err = ioctl(sockfd, SIOCADDRT, &route);
  if ((err) < 0) {
    fprintf(stderr, "ioctl: %s\n",  "mahdi MOAHMMADI Error");
    perror("ioctl set route");
    return -1;
  }
  ++g_success_num;
  return 1;
}

/**
* Set ip function
*/
int set_ip(char *iface_name, char *ip_addr, char *gateway_addr,char *subnet_mask)
{
  if(!iface_name)
    return -1;
  struct ifreq ifr;
  struct sockaddr_in sin;
  int sockfd = create_socket();

  sin.sin_family = AF_INET;

  // Convert IP from numbers and dots to binary notation
  inet_aton(ip_addr,&sin.sin_addr);

  /* get interface name */
  strncpy(ifr.ifr_name, iface_name, IFNAMSIZ);

  /* Read interface flags */
  generic_ioctrlcall(sockfd, (u_long *)"SIOCGIFFLAGS", &ifr);

  /*
  * Expected in <net/if.h> according to
  * "UNIX Network Programming".
  */
  #ifdef ifr_flags
  # define IRFFLAGS       ifr_flags
  #else   /* Present on kFreeBSD */
  # define IRFFLAGS       ifr_flagshigh
  #endif
  // If interface is down, bring it up
  if (ifr.IRFFLAGS | ~(IFF_UP)) {
    ifr.IRFFLAGS |= IFF_UP;
    generic_ioctrlcall(sockfd, (u_long *)"SIOCSIFFLAGS", &ifr);
  }
  // Set route
  set_route(sockfd, gateway_addr    ,  &sin,subnet_mask,iface_name);
  memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr)); 
  // Set interface address
  if (ioctl(sockfd, SIOCSIFADDR, &ifr) < 0) {
    fprintf(stderr, "Cannot set IP address. ");
    perror(ifr.ifr_name);
    return -1;
  }             
  ++g_success_num;
  #undef IRFFLAGS 
  struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_addr;
  inet_pton(AF_INET, subnet_mask, &addr->sin_addr);
  ioctl(sockfd, SIOCSIFNETMASK, &ifr);
  ++g_success_num;
  return 0;
}


void setIPv4(char * ip,char * gw,char * netmask)
{
	char cmd[128]={0};
	//network interface
	char nwkInf[64]="enp0s31f6";

	//link down command in Linux
	sprintf(cmd,"ip link set %s down",nwkInf);
	system(cmd); 
	
	
	memset(cmd,0x00,64);
	//command to set ip address, netmask
	sprintf(cmd,"ifconfig %s %s netmask %s",nwkInf,ip,netmask);
	system(cmd);	 
	//printf("\ncmd : %s",cmd); fflush(stdout);
	memset(cmd,0X00,64);

	//command to set gateway
	sprintf(cmd,"route add default gw %s %s",gw,nwkInf);
	system(cmd); 

	memset(cmd,0X00,64);
	//link up command
	sprintf(cmd,"ip link set %s up",nwkInf);
	system(cmd); 
	
}

void get_interface_name(char *interface_name)
{
    struct ifaddrs *addrs,*tmp;

    getifaddrs(&addrs);
    tmp = addrs;

    while (tmp)
    {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET){
            printf("%s\n", tmp->ifa_name);
            if(tmp->ifa_name[0]=='e'){
                strncpy(interface_name,tmp->ifa_name,strlen(tmp->ifa_name));
                break;
 
            }
 
        }
      tmp = tmp->ifa_next;
    }
    
    freeifaddrs(addrs);
}

int validate_number(char *str) {
   while (*str) {
      if(!isdigit(*str)){ //if the character is not a number, return false
         return 0;
      }
      str++; //point to next character
   }
   return 1;
}

int validate_ip(char *rip) { //check whether the IP is valid or not
   int i, num, dots = 0;
   char ip[64] = {0};
   strncpy(ip,rip,strlen(rip));
 
   char *ptr;
   if (ip == NULL)
      return 0;
      ptr = strtok(ip, "."); //cut the string using dor delimiter
      if (ptr == NULL)
         return 0;
   while (ptr) {
      if (!validate_number(ptr)) //check whether the sub string is holding only number or not
         return 0;
         num = atoi(ptr); //convert substring to number
         if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, "."); //cut the next part of the string
            if (ptr != NULL)
               dots++; //increase the dot count
         } else
            return 0;
    }
    if (dots != 3) //if the number of dots are not 3, return false
       return 0;
      return 1;
}


int check_configed()
{
    int ret=0;
    FILE* fp = fopen("netsetup.txt", "wr");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    char line[256];
    fgets(line, sizeof(line), fp);
    if(strcmp(line,"3")==0)
        ret=0;
    else
        ret=-1;

    /*while (fgets(line, sizeof(line), fp)) {
         note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) 
        printf("%s", line); 
    }*/
    fclose(fp);
    return 0;
}

int write_file()
{
    FILE* fp = fopen("netsetup.txt", "w");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    char line[256];
    sprintf(line,"%d",g_success_num);
    fputs(line, fp);
    fclose(fp);
    return 0;
}

int main()
{
    char interface_name[64]={0};

    get_interface_name(interface_name);
    check_configed();

    printf("Please enter network settings for the internal interface. If you are on the onprem network as the appliance, press ENTER when prompted for a gateway.\n");

    char ip[32]={0};
    printf("IP Address:");
    scanf("%31s",ip);
 
    while(!validate_ip(ip))
    {
        printf("ip address Not valid\n");
        printf("IP Address:");
        scanf("%31s",ip);
 
    }
    printf("Subnet mask:");
    char subnet_mask[32]={0};
    scanf("%31s",subnet_mask);
    while(!validate_ip(subnet_mask))
    {
        printf("subnet mask Not valid\n");
        printf("Subnet mask:");
        scanf("%31s",subnet_mask);
 
    }
 

    printf("Gateway:");
    char gateway[32]={0};
    scanf("%31s",gateway);
    while(!validate_ip(gateway))
    {
        printf("gateway Not valid\n");
        printf("Gateway:");
        scanf("%31s",gateway);
 
    }
    printf("%s %s %s\n ",ip,subnet_mask,gateway); 
    set_ip(interface_name, ip, gateway,subnet_mask);
	//calling function to set network settings
	//setIPv4("192.168.168.122","10.103.56.1","255.255.255.0");
	return 0;
}
