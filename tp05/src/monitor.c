
// void close_parameters(parameters *param)
// {
//   munmap(param, sizeof(parameters));
// }

// parameters *open_parameters(const char *path)
// {
//   int fd; /* file descriptor associated to the parameters shm */
//   parameters *params; /* pointer to the "parameters" structure */
//   size_t size; /* mailbox size */

//   fd = shm_open(path, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//   if (fd == -1) {
//       log_error("shm_open() problem!");
//       return NULL;
//   }

//   size = sizeof(parameters);
//   params = (parameters *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,
//   (off_t) 0);↪
//   if (params == MAP_FAILED) {
//     log_error("mmap() problem!");
//     return NULL;
//   }

//   return params;
// }

// void modify_parameters(parameters *params)
// {
//   semaphore *mutex;

//   log_info("Monitor> Trying to access Dispenser (PID: %d)...", params->pid_gui);
//   mutex = open_semaphore(MUTEX_NAME, 0);
//   if (mutex == NULL) {
//     log_error("Monitor> open_semaphore() problem!");
//     exit(EXIT_FAILURE);
//   }

//   log_info("Monitor> Mutex is going to be preempted.");
//   log_info("Monitor> Trying to setup bad key...");
//   P(mutex);

//   strcpy(params->key, "Manon");
//   strcpy(params->tap, "closed");
//   strcpy(params->drink, "water");
//   V(mutex);

//   log_info("Monitor> Mutex has been released.");
//   sleep(10);

//   log_info("Monitor> Mutex is going to be preempted.");
//   log_info("Monitor> Trying to setup good key...");
//   P(mutex);

//   /* Test "Manon des sources" */
//   strcpy(params->key, "Znaba qrf fbheprf");
//   strcpy(params->tap, "closed");
//   strcpy(params->drink, "water");
//   V(mutex);
//   log_info("Monitor> Mutex has been released.");
//   sleep(10);

//   log_info("Monitor> Mutex is going to be preempted.");
//   log_info("Monitor> Trying to open tap...");
//   P(mutex);
//   strcpy(params->tap, "opened");
//   strcpy(params->drink, "water");
//   V(mutex);
//   log_info("Monitor> Mutex has been released.");
//   sleep(10);

//   log_info("Monitor> Mutex is going to be preempted.");
//   log_info("Monitor> Trying to choose \"mint\" syrup...");
//   P(mutex);
//   strcpy(params->drink, "mint");
//   V(mutex);
//   log_info("Monitor> Mutex has been released.");
//   sleep(10);

//   log_info("Monitor> Mutex is going to be preempted.");
//   log_info("Monitor> Trying to choose \"grenadine\" syrup...");
//   P(mutex);
//   strcpy(params->drink, "grenadine");
//   V(mutex);
//   log_info("Monitor> Mutex has been released.");
//   sleep(40);

//   log_info("It's time to exit....");
//   log_info("Monitor> Mutex is going to be preempted.");
//   log_info("Monitor> Trying to close Dispenser (PID: %d)...", params->pid_gui);
//   P(mutex);
//   strcpy(params->tap, "closed");
//   sleep(1);
//   params->ending_flag = ON;
//   V(mutex);
//   sleep(1);
//   log_info("Bye...");
// }

// int main(int argc, char **argv)
// {
//   parameters *params;
//   log_info("Monitor> ON");
//   params = open_parameters(PARAM_PATH);

//   if (params != NULL) {
//     modify_parameters(params);
//     close_parameters(params);
//   }

//   log_info("Monitor> OFF");

//   exit(EXIT_SUCCESS);
// }

// // #include <sys/mman.h>
// // #include <fcntl.h>
// // #include <stdio.h>
// // #include <errno.h>
// // #include <stdlib.h>
// // #include <unistd.h>
// // #include <string.h>

// // #define SHM_NAME "/saperlipopette"
// // #define SHM_SIZE 256

// // /*
// //     Número de série
// //     Indicador de extinção (0 ou 1)
// //     Senha criptografada
// //     Estado da válvula ("aberta", "fechada")
// //     Bebida selecionada
// // */

// // typedef struct
// // {
// //     int serial_number;
// //     int shutdown_flag;
// //     char password[SHM_SIZE];
// //     char valve_state[SHM_SIZE];
// //     char beverage[SHM_SIZE];
// // } Configuration;

// // // const int SHM_SIZE = sizeof(Configuration);

// // int open_shared_memory(Configuration **config)
// // {
// //     int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
// //     if (shm_fd == -1)
// //     {
// //         perror("Erro tentando abrir a shared memory");
// //         return -1;
// //     }

// //     /*
// //     O mmap() é uma chamada de sistema que cria um novo mapeamento no espaço de endereço virtual do processo de chamada. Ele permite que um processo mapeie regiões de arquivos ou dispositivos diretamente em sua memória virtual, facilitando o acesso a esses dados.
// //     - addr: O endereço inicial para o novo mapeamento (pode ser NULL para deixar o kernel escolher)
// //     - length: O tamanho do mapeamento (deve ser maior que 0)
// //     - prot: A proteção de memória desejada para o mapeamento (PROT_READ, PROT_WRITE, etc.)
// //     - flags: Determina se as atualizações no mapeamento são visíveis para outros processos (MAP_SHARED, MAP_PRIVATE)
// //     - fd: O descritor de arquivo para o objeto a ser mapeado
// //     - offset: O deslocamento no arquivo a partir do qual o mapeamento deve começar
// //     */
// //     *config = mmap(NULL, sizeof(Configuration), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
// //     if (*config == MAP_FAILED)
// //     {
// //         perror("Erro mapeando a shared memory.");
// //         close(shm_fd);
// //         return -1;
// //     }

// //     return shm_fd;
// // }

// // void save_changes_to_shared_memory(Configuration *config)
// // {
// //     if (msync(config, sizeof(Configuration), MS_SYNC) == -1)
// //     {
// //         perror("Error syncing shared memory");
// //     }
// // }

// // void test_config(Configuration *config)
// // {
// //     strcpy(config->password, "Znaba qrf fbheprf");
// //     strcpy(config->valve_state, "closed");
// //     strcpy(config->beverage, "water");

// //     sleep(5);
// //     strcpy(config->valve_state, "opened");
// //     strcpy(config->beverage, "water");
// // }
// // void set_fountain_state(Configuration *config, const char *state, const char *beverage)
// // {
// //     if (strcasecmp(state, "open") != 0 && strcasecmp(state, "close") != 0)
// //     {
// //         printf("Invalid state. Use 'open' or 'close'.\n");
// //         return;
// //     }

// //     strncpy(config->valve_state, state, SHM_SIZE - 1);
// //     config->valve_state[SHM_SIZE - 1] = '\0';

// //     strncpy(config->beverage, beverage, SHM_SIZE - 1);
// //     config->beverage[SHM_SIZE - 1] = '\0';

// //     // Synchronize changes to shared memory
// //     if (msync(config, sizeof(Configuration), MS_SYNC) == -1)
// //     {
// //         perror("Error syncing shared memory");
// //     }
// //     else
// //     {
// //         printf("Valve changed to: %s\n", config->valve_state);
// //         printf("Selected beverage: %s\n", config->beverage);
// //     }
// // }

// // void monitor(Configuration *config)
// // {
// //     printf("Serial: %d\n", config->serial_number);
// //     printf("Flag: %d\n", config->shutdown_flag);
// //     printf("Válvula: %s\n", config->valve_state);
// //     printf("Bebida: %s\n", config->beverage);
// // }

// // void reset_configuration(Configuration *config)
// // {
// //     strcpy(config->password, "Znaba qrf fbheprf");
// //     strcpy(config->valve_state, "close");
// //     strcpy(config->beverage, "water");
// //     config->shutdown_flag = 1;

// //     msync(config, SHM_SIZE, MS_SYNC);
// //     printf("Configuração restaurada para o estado original.\n");
// // }

// // void open_valve(Configuration *config)
// // {
// //     strcpy(config->valve_state, "open");

// //     msync(config, SHM_SIZE, MS_SYNC);
// //     printf("Válvula alterada para: %s\n", config->valve_state);
// // }

// // void choose_drink(Configuration *config)
// // {
// //     char drink[SHM_SIZE];
// //     printf("Escolha uma bebida: ");
// //     scanf("%s", drink);

// //     strncpy(config->beverage, drink, SHM_SIZE - 1);
// //     config->beverage[SHM_SIZE - 1] = '\0';

// //     msync(config, SHM_SIZE, MS_SYNC);
// //     printf("Bebida selecionada: %s\n", config->beverage);
// // }

// // void close_shared_memory(Configuration *config, int shm_fd)
// // {
// //     /*
// //     munmap() remove mapeamentos de memória mapeada para um determinado intervalo de endereços.
// //     - addr: o endereço inicial do intervalo de memória a ser desmapeado
// //     - len: o tamanho, em bytes, do intervalo de memória a ser desmapeado
// //     */
// //     munmap(config, SHM_SIZE);
// //     close(shm_fd);
// // }

// // void bypass_password(Configuration *config)
// // {
// //     char decoded_password[32];

// //     strcpy(config->password, "Znaba qrf fbheprf"); // Pesquisar sobre o msync

// //     /*
// //     A função msync() é usada para sincronizar os dados de uma região de memória mapeada com o sistema de arquivos. Isso significa que ela força a gravação das alterações feitas na memória de volta para o disco.
// //     Para usar a msync() em uma shared memory:
// //         1. Crie a shared memory usando mmap().
// //         2. Faça as alterações desejadas na memória.
// //         3. Chame msync() para forçar a gravação das alterações no disco.
// //     */
// //     save_changes_to_shared_memory(config);
// // }

// // /*

// //     MAIN

// // */

// // int main()
// // {
// //     Configuration *config;

// //     int shared_memory = open_shared_memory(&config);

// //     test_config(config);
// //     close_shared_memory(config, shared_memory);

// //     return 0;
// // }

#include <stdio.h>
#include <unistd.h> /* close */
#include <sys/mman.h> /* shm_open et shm_unlink */
#include <fcntl.h>
#include <string.h>

typedef struct {
  int a;
  int b;
  char c[256];
  char d[256];
  char e[256];
} shm_data;

int main() {

  int shmd = shm_open("/saperlipopette", O_RDWR, 0600);
  if (shmd == -1) { /* Gestion d'erreur */
  }
  shm_data* data = mmap(NULL,            /* adresse virtuelle ou projeter le début de page */
    sizeof(shm_data),    /* taille de projection */
    PROT_READ | PROT_WRITE, /* accès aux pages */
    MAP_SHARED,             /* type de segment */
    shmd,                   /* descripteur du segment */
    0                       /* offset de projection */
  );
  /* ... beaucoup de travail sur la mémoire */
  printf("%d %d %s %s %s\n", data->a, data->b, data->c, data->d, data->e);
  // 8543 0 xxxxx xxx xxxxxxx closed water
  // Manon des sources

  // strcpy(data->c, "Manon des sources");
  // for (int i = 0; i < 26; i++) {
  //   for (int j = 0; j < 17; j++) {
  //     if (data->c[j] == 'z') {
  //       data->c[j] = 'a';
  //     } else if (data->c[j] == 'Z') {
  //       data->c[j] = 'A';
  //     } else {
  //       data->c[j] += 1;
  //     }
  //   }
  //   data->c[5] = ' ';
  //   data->c[9] = ' ';
  //   printf("%d %d %s %s %s\n", data->a, data->b, data->c, data->d, data->e);
  //   sleep(1);
  // }


  strcpy(data->c, "Znaba qrf fbheprf");
  strcpy(data->d, "opened");
  munmap(data, sizeof(shm_data));
  close(shmd);
  return 0;
}