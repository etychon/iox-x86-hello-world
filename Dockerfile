FROM devhub-docker.cisco.com/iox-docker/ir800/base-rootfs as builder
RUN opkg update
RUN opkg install iox-toolchain curl
RUN mkdir -p /var/helloworld/
COPY helloworld.c /var/helloworld/
WORKDIR /var/helloworld/
RUN gcc helloworld.c -o helloworld

FROM devhub-docker.cisco.com/iox-docker/ir800/base-rootfs
RUN mkdir -p /var/helloworld/
COPY --from=builder /var/helloworld/helloworld /var/helloworld
COPY --from=builder /usr/bin/curl /usr/bin/curl
COPY start.sh /
RUN chmod +x /var/helloworld/helloworld
CMD ["/bin/sh", "/start.sh"]
