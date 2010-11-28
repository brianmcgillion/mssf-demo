#!/bin/bash

while [ $# -ge 1 ]; do
    case $1 in
	--iface)
	    qdbusxml2cpp -c DBusServiceIfAdaptor -a dbusserviceifadaptor.h:dbusserviceifadaptor.cpp ./daemon/com.meego.mssf.xml
	    ;;
	--proxy)
	    qdbusxml2cpp -v -c MssfDbusIf -p mssfdbusif.h:mssfdbusif.cpp ./daemon/com.meego.mssf.xml
	    ;;
    esac
    shift
done    

exit