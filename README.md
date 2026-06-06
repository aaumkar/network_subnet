# Network Subnet Helper

A network subnet helper for IPv4 addresses and subnets. 

Users should be able to enter their subnets masks using digit-by-digit inputs.
```
 ^  ^  ^   ^  ^  ^   ^  ^  ^   ^  ^  ^ 
[0][0][0].[0][0][0].[0][0][0].[0][0][0]
 v  v  v   v  v  v   v  v  v   v  v  v  
```

After entering the subnet, the view should show the IP ranges
e.g. 
255.255.255.0 -> x.x.x.0-255
255.255.0.0 -> x.x.0-255.0-255

Main calculation is when the subnet octets are not 0 or 255. 

Another version would be to get IP and subnet. e.g. 10.12.12.56/24 and provide the subnet range.

Screen is 128x64 px
┌────────────────────────────────────────────┐
│                                            │
│                                            │
│                                            │
│                                            │
│                                            │
│                                            │
│                                            │
│                                            │
│                                            │
│                                            │
└────────────────────────────────────────────┘