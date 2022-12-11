/**
 * File: assn4.c
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022.12.03
 * OS: macOS 13.0.1
 * IDE Environment: Visual Studio Code 1.74.0
 * GCC version: gcc 14.0.0
 * C standard: C99
 * Encoding: UTF-8
 * End of Line Sequence: LF
 * Naming Convention: snake_case
*/

// 필요한 헤더파일을 include한다. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h" // 본 프로그램의 함수들이 정의된 헤더파일

/**
 * 주어진 파일에서 playlist를 불러오는 함수
 * 매개변수 filename: playlist가 저장된 파일의 이름
 * 리턴값: playlist linkedlist의 head dummy 노드 ; 정상적으로 불러오지 못했을 경우 NULL
*/
Node* load_playlist(char *filename);

/**
 * playlist linkedlist의 head dummy node가 주어졌을 때, 사용자에게 음악 정보를 입력받아 playlist에 추가하는 함수
 * 매개변수 head: playlist linkedlist의 head dummy node
 * 리턴값: 성공적으로 추가되었거나 용량 초과인 경우 0, 그렇지 않을 경우 -1
*/
int add_music(Node *head);

int main(void) {
    char filename[35]; // playlist를 불러올 파일 이름, 혹은 저장할 파일 이름
    Node *head = NULL; // playlist linkedlist의 head dummy node
    while (1) {
        printf("음악 리스트 파일 이름을 입력해주세요. >> "); // playlist를 불러올 파일 이름을 입력하라는 prompt를 출력한다. 
        scanf("%s", filename); // playlist를 불러올 파일 이름을 입력받는다. 
        if ((head = load_playlist(filename)) != NULL) break; // playlist를 불러올 파일 이름을 입력받았을 때, 해당 파일이 존재하여 정상적으로 불러온 경우 반복문을 멈춘다. 
        printf("유효하지 않은 파일입니다. "); // 정상적으로 불러오지 못한 경우 유효하지 않은 파일임을 알리는 메시지를 출력하고 다시 입력받는다. 
    }

    char command[20]; // 사용자가 입력한 명령어를 저장할 변수를 선언한다. 
    while (1) {
        // 사용자에게 명령어를 입력받는다.
        printf("\n");
        printf("명령어를 입력해주세요. >> ");
        scanf("%s", command);

        if (strcmp(command, "show") == 0) { // 사용자가 show 메뉴를 선택한 경우
            show_fn(head, "PLAYLIST"); // playlist를 출력한다.
        } else if (strcmp(command, "show_favorites") == 0) { // 사용자가 show_favorites 메뉴를 선택한 경우
            int n; // 추출할 음악의 개수를 저장할 변수를 선언한다.
            printf("상위 몇 개의 음악을 추출할까요? >> "); scanf("%d", &n); // 추출할 음악의 개수를 입력받는다. 
            // 사용자가 입력한 개수 만큼의 음악을 preference 순으로 추출하여 출력한다. 이때, 사용자가 입력한 숫자가 전체 음악의 개수보다 많은 경우, 에러 메시지를 출력한다. 
            if (show_favorites_fn(head, n) == -1) printf("추출하고자 하는 음악의 수가 전체 음악의 수보다 많습니다. \n");
        } else if (strcmp(command, "add") == 0) { // 사용자가 add 메뉴를 선택한 경우
            // 사용자의 입력을 받아 playlist에 음악을 추가한다. 이때, 이미 playlist에 존재하는 음악을 추가하려고 할 경우, 에러 메시지를 출력한다.
            if (add_music(head) == -1) printf("해당 음악이 이미 플레이리스트 내에 존재합니다. \n");
        } else if (strcmp(command, "delete") == 0) { // 사용자가 delete 메뉴를 선택한 경우
            char title[15]; // 삭제할 음악의 타이틀을 저장할 변수를 선언한다.
            printf("삭제할 음악의 타이틀을 입력해주세요. >> "); scanf("%s", title); // 삭제할 음악의 타이틀을 입력받는다.
            // 사용자가 입력한 타이틀의 음악을 playlist에서 삭제한다. 이때, playlist에 존재하지 않는 음악을 삭제하려고 할 경우, 에러 메시지를 출력한다.
            if (delete_fn(head, title) == -1) printf("플레이리스트에 해당 음악(%s)이 없습니다. \n", title);
        } else if (strcmp(command, "exit") == 0) { // 사용자가 exit 메뉴를 선택한 경우
            // 프로그램을 종료하기 전에 플레이리스트를 저장할 파일 이름을 입력받는다. 
            printf("저장할 파일명을 입력해주세요. >> ");
            scanf("%s", filename);
            exit_fn(head, filename); // playlist를 파일에 저장하고 프로그램의 resource를 정리한 뒤 프로그램을 종료한다.
            break;
        } else { // 사용자가 유효하지 않은 명령어를 입력한 경우
            printf("유효하지 않은 명령어입니다. \n"); // 사용자에게 유효하지 않은 명령어임을 알려주고 다시 명령어를 입력받기 위해 반복한다. 
        }
    }

    return 0;
}

Node* load_playlist(char *filename) {
    FILE *fp = fopen(filename, "r"); // 파일을 읽기 모드로 열어준다.
    if (fp == NULL) return NULL; // 파일이 존재하지 않는 경우 NULL을 반환한다.
    
    Node *head = (Node*) malloc(sizeof(Node)); // head dummy node를 동적할당한다.
    head->next = NULL; // head dummy node의 next를 NULL로 초기화한다.

    Music music; // 새로운 음악 정보를 저장할 구조체를 선언한다.
    while (1) {
        // 파일에서 음악 정보를 입력받는다. 이때, 파일의 끝에 도달했다면 반복문을 멈춘다.
        if (fscanf(fp, "%s %s %f %f", music.title, music.artist, &music.size, &music.pref) == EOF) break;

        if (get_total_size(head) + music.size > 50) { // 음악의 용량이 초과된 경우
            printf("용량 초과! 음악(%s)은 추가되지 않았습니다. \n", music.title); // 사용자에게 용량 초과임을 알려준다. 
            continue;
        }

        add_fn(head, &music, crit_title); // 음악 정보를 플레이리스트에 추가한다.
    }
    fclose(fp); // 파일을 닫아준다.
    return head; // 플레이리스트의 head dummy node를 반환한다.
}

int add_music(Node *head) {
    Music music; // 새로운 음악 정보를 저장할 구조체를 선언한다.
    // 사용자에게 추가할 음악 정보를 입력받는다.
    printf("추가할 음악의 타이틀을 입력해주세요. >> "); scanf("%s", music.title); 
    printf("추가할 음악의 아티스트를 입력해주세요. >> "); scanf("%s", music.artist);
    printf("추가할 음악의 용량을 입력해주세요. >> "); scanf("%f", &music.size);
    printf("추가할 음악의 선호도를 입력해주세요. >> "); scanf("%f", &music.pref);

    if (get_total_size(head) + music.size > 50) { // 음악의 용량이 초과된 경우
        printf("용량 초과! 음악(%s)은 추가되지 않았습니다. \n", music.title); // 사용자에게 용량 초과임을 알려준다. 
        return 0; // 에러 메시지가 필요하지 않다는 신호로 0을 출력한다. 
    }
    
    // 음악의 중복 여부를 확인한다.
    Node *cursor = head; // cursor를 head dummy node로 초기화한다.
    while (cursor != NULL) {
        if (strcmp(cursor->data.title, music.title) == 0) return -1; // 제목이 동일한 음악이 존재하는 경우 -1을 반환한다. 
        cursor = cursor->next; // cursor를 다음 노드로 이동시킨다.
    }
    add_fn(head, &music, crit_title); // 음악 정보를 플레이리스트에 추가한다. 
    return 0; // 성공적으로 playlist에 음악을 추가했으므로 0을 반환한다. 
}
