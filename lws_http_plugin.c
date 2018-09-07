#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "lws_http.h"
#include "lws_http_plugin.h"

void lws_notfound_handler(lws_http_conn_t *c, int ev, void *p)
{
    char data[1024] = {0};

    sprintf(data, "%s",
              "HTTP/1.1 404 NOT FONUD\r\n"
              "Content-Type: text/html\r\n"
              "Connection: close\r\n"
              "\r\n");

    c->send(c->sockfd, data, strlen(data));
    c->close_flag = 1;
}

void lws_default_handler(lws_http_conn_t *c, int ev, void *p)
{
    struct http_message *hm = p;
    char data[1024] = {0};

    if (hm && ev == LWS_EV_HTTP_REQUEST) {
        if (c->send == NULL) {
            c->close_flag = 1;
            return ;
        }
    
        sprintf(data, "%s",
                  "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "Connection: close\r\n"
                  "\r\n"
                  "<html><body><h>Enjoy your smart home camera!</h><br/><br/>"
                  "<ul style=\"list-style-type:circle\">"
                  "<li><a href=\"/devices/deviceinfo\"> view device information </a></li>"
                  "<li><a href=\"/sys/reboot\"> reboot device </a></li>"
                  "</ul>"
                  "</body></html>");

        c->send(c->sockfd, data, strlen(data));
        c->close_flag = 1;
    }
}

void lws_hello_handler(lws_http_conn_t *c, int ev, void *p)
{
    struct http_message *hm = p;
    char data[1024] = {0};

    if (hm && ev == LWS_EV_HTTP_REQUEST) {
        if (c->send == NULL) {
            c->close_flag = 1;
            return ;
        }

        sprintf(data, "%s",
                  "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "Connection: close\r\n"
                  "\r\n"
                  "<html><body><h>Hello LWS!</h><br/><br/>"
                  "</body></html>");

        c->send(c->sockfd, data, strlen(data));
        c->close_flag = 1;
    }
}

