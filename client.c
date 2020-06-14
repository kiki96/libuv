#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <uv.h>

int *fd;

uv_fs_t req;
uv_fs_t req_read;
uv_fs_t write_req;

uv_timer_t timer1;
uv_fs_poll_t poll1;
uv_stream_t* stream;

static char buffer[1024];
static uv_buf_t iov;
static uv_buf_t wr_a = {.base = "a", .len = 1};

void timer1_cb(uv_timer_t *handle) {
    //printf("Dopisano slovo a!\n");
    uv_fs_write(uv_default_loop(), &write_req, *fd, &wr_a, 1, -1, NULL);
}

void poll1_cb(uv_fs_poll_t *handle){
    //printf("Poll uocio promjenu!\n");
    iov = uv_buf_init(buffer, sizeof(buffer));
    uv_write_t request;
    uv_fs_read(uv_default_loop(), &req_read, *fd, &iov, 1, 0, NULL);
    uv_write(&request, stream, &iov, 1, NULL);
}
    

int main(int argc, char **argv) {
	struct sockaddr_in dest;
    
    int pom = uv_fs_open(uv_default_loop(), &req, "file.txt", O_RDWR | O_APPEND, 0, NULL);
    fd=&pom; 
    
    uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));

    uv_timer_init(uv_default_loop(), &timer1);
    uv_fs_poll_init(uv_default_loop(), &poll1);
    uv_tcp_init(uv_default_loop(), socket);

    uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));
    uv_ip4_addr("0.0.0.0", 7000, &dest);
    uv_tcp_connect(connect, socket, (const struct sockaddr*)&dest, NULL);
    stream = connect->handle;
    
    //uv_timer_start(&timer1, timer1_cb, 15000, 10000);
    uv_fs_poll_start(&poll1, (uv_fs_poll_cb) poll1_cb, "file.txt", 3000);

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
