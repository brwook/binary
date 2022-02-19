FROM ubuntu:18.04

RUN apt update
RUN apt-get install -y xinetd gcc-multilib qemu-kvm
RUN apt-get install -y python3 python3-pip
RUN apt-get install -y cpio
RUN apt-get install -y git
ENV TERM=linux

RUN pip3 install git+https://github.com/Juvenal-Yescas/mediafire-dl
COPY files/ /chall
COPY xinetd /etc/xinetd.d/root
WORKDIR /chall

RUN chmod 777 /chall
RUN chmod 460 /chall/*
RUN chmod +x /chall/test.sh
RUN chmod +x /chall/download.py

EXPOSE 1800

CMD ["/usr/sbin/xinetd","-dontfork"]
