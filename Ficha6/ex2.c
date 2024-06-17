#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

    // checkar em todos se fd < 0
    int input_fd = open("/etc/passwd", O_RDONLY);
    int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int error_fd = open("erros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    //cópias dos originais
    int original_stout = dup(STDOUT_FILENO);

    dup2(input_fd,STDIN_FILENO);
    dup2(output_fd,STDOUT_FILENO);
    dup2(error_fd, STDERR_FILENO);

    // é a forma correta de escrever para o ficheiro output, não usar print
    write(1,"ola",3);

    close(input_fd);
    close(output_fd);
    close(error_fd);

    if (fork() == 0){
        char buf[100];
        int read_bytes = 0;
        while((read_bytes = read(0,buf,100)) > 0){
            write(STDERR_FILENO, buf,read_bytes);
            write(STDOUT_FILENO, buf,read_bytes);
        }

    }

    // para voltar a colocar nos originais
    dup2(original_stout,STDOUT_FILENO);
    // fechar as cópias dos originais
    close(original_stout);

    write(1,"terminei\n",9);


    return 0;
}
