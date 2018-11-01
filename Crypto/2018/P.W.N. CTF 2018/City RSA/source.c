#include <stdio.h>
#include <string.h>
#include "city_rsa.h"

int read_config(const char* path, char* p_str, char* q_str, char* p_inv_str,
                char* d_str, char* e_str, char* d_p_str, char* d_q_str) {
    FILE* f;
    if ((f = fopen(path, "r")) == NULL) {
        perror("Config can't be read");
        return 0;
    }

    if(7 != fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
                   p_str, q_str, p_inv_str,
                   d_str, e_str, d_p_str, d_q_str)) {
        puts("Config file has invalid format!\n");
        return 0;
    }
    return 1;
}

int main(int argc, const char** argv) {
    city_rsa_config cfg;
    /* RSA parameters */
    char p_str[1024];
    char p_inv_str[1024];
    char q_str[1024];
    char d_str[1024];
    char e_str[1024];
    char d_q_str[1024];
    char d_p_str[1024];
    char input[32];
    char input_hex[67];
    char result[1024];
    int i;

    if (argc < 2) {
        puts("Call: cityrsa path_to_config\n");
        return 1;
    }

    if (!read_config(
            argv[1], p_str, q_str, p_inv_str, d_str, e_str,
            d_p_str, d_q_str)) {
        return 1;
    }

    printf("Enter message:");
    fflush(stdout);
    fgets(input, sizeof(input_hex) / 2, stdin);


    input_hex[0] = '0';
    input_hex[1] = 'x';
    for(i = 0; i <= strlen(input); i++){
        sprintf(input_hex + 2 + i*2, "%02X", input[i]);
    }

    puts(input_hex);

    if (strstr(input_hex, "594553") != NULL) {
        // Security measure, don't agree to anything
        return 1;
    }

    /* Sign via RSA */
    city_rsa_init(&cfg, p_str, q_str, p_inv_str, d_str, e_str, d_p_str, d_q_str);
    //city_print_config(&cfg);
    city_rsa_sign(&cfg, result, input_hex);
    printf("The signature of your message is: 0x%s\n", result);

    return 0;
}