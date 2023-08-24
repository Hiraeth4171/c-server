#!/bin/bash 
# allow ./server to use ports below 1024 without sudo.
setcap 'cap_net_bind_service=+ep' ./server
