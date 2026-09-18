#include <stdio.h>
#include <string.h>

void xorEncryptDecrypt(char *data, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0; data[i] != '\0'; ++i) {
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
        printf("Enter filename to save encrypted data: ");
        scanf("%s", filename);
        printf("Enter the key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return 1;
        }

        xorEncryptDecrypt(message, key);
        fwrite(message, sizeof(char), strlen(message), file);
        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        printf("Enter filename to read encrypted data: ");
        scanf("%s", filename);
        printf("Enter the key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Error opening file for reading.\n");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *encryptedData = (char *)malloc((fileSize + 1) * sizeof(char));
        if (encryptedData == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return 1;
        }

        fread(encryptedData, sizeof(char), fileSize, file);
        encryptedData[fileSize] = '\0';
        fclose(file);

        xorEncryptDecrypt(encryptedData, key);
        printf("Decrypted message: %s\n", encryptedData);
        free(encryptedData);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}