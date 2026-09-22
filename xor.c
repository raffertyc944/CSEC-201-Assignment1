#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void xorEncryptDecrypt(char *data, const char *key, int dataLen) {
    int keyLen = strlen(key);

    if (keyLen == 0) {
        return;
    }

    for (int i = 0; i <dataLen; ++i) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice[10], message[256], filename[256], key[256];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", choice);

    if (strcmp(choice, "encrypt") == 0) {
        //Input was getting stuck on \n
        getchar();

        printf("Enter the string to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character

        if (strlen(message) == 0) {
            printf("Error: message cannot be empty.\n");
            return 1;
        }
        printf("Enter filename to save encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename. "\n")] = '\0';
        printf("Enter the key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        if (strlen(key) == 0) {
            printf("Error: key cannot be empty.\n");
            return 1;
        }

        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return 1;
        }

        int messageLen = strlen(message);
        xorEncryptDecrypt(message, key, messageLen);
        fwrite(message, sizeof(char), messageLen, file);
        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        getchar();

        printf("Enter filename to read encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        printf("Enter the key: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        if (strlen(key) == 0) {
            printf("Error: key cannot be empty.\n");
            return 1;
        }

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Error opening file for reading.\n");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        if (fileSize == 0) {
            printf("Error: file is empty.\n");
            fclose(file);
            return 1;
        }
        char *encryptedData = (char *)malloc((fileSize + 1) * sizeof(char));
        if (encryptedData == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return 1;
        }

        fread(encryptedData, sizeof(char), fileSize, file);
        encryptedData[fileSize] = '\0';
        fclose(file);

        xorEncryptDecrypt(encryptedData, key, fileSize);
        printf("Decrypted message: %s\n", encryptedData);
        free(encryptedData);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}