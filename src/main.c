#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "time.h"

bool isValid(int q[], int n, char **grid){
    bool color_used[26] = {false};
    for (int r = 0; r < n; r++){
        int c = q[r];
        int color_idx = grid[r][c] - 'A';//buat A jadi 0, B jadi 1, dan seterusnya
        
        //validasi agar hanya A-Z yang dibaca
        if (color_idx < 0 || color_idx > 26){
            continue;
        }
        //jika warna sudah dipakai maka return false
        if (color_used[color_idx]){
            return false;
        }
        color_used[color_idx] = true;//jika warna belum dipakai, maka buat menjadi true

        if (r > 0){
            if (abs(q[r] - q[r - 1]) <= 1){
                return false;
            }
            
        }
        
    }
    return true;
}


// fungsi untuk mencari semua kemungkinan posisi queen dengan baris dan kolom sudah pasti berbeda
bool nextPerm(int q[], int n){ 
    int i = n -2;
    while (i >= 0 && q[i] >= q[i + 1]){
        i--;
    }
    if (i < 0){ //jika i < 0, maka semua variasi posisi queen sudah dicoba
        return false;
    }
    int j = n -1;
    while (q[j] <= q[i]){
        j--;
    }
    int temp = q[i];
    q[i] = q[j];
    q[j] = temp;

    for (int k = i +1,l = n -1; k < l; k++, l--){
        temp = q[k];
        q[k] = q[l];
        q[l] = temp;
    }
    return true;
}
int main(){
    char nama_file[100], character; 
    int n; //n sebagai ukuran grid (n x n)
    printf("masukkan nama file yang ingin dibuka : ");
    scanf("%s", nama_file);

    FILE *file = fopen(nama_file, "r");
    if (file == NULL)
    {
        printf("Gagal membuka file %s. Pastikan nama file sudah sesuai\n", nama_file);
        return 1;
    }
    printf("File %s berhasil dibuka\n", nama_file);

    //Validasi baris dan kolom
    int count = 0; int rows = 0;
    char line[1024];
    while (fgets((line), sizeof(line), file))
    {
        int character_in_line = 0;
        for (int i = 0; i < line[i] != '\0'; i++)
        {
            if (line[i] >= 'A' && line[i] <= 'Z')
            {
                character_in_line++;;
            }
            
        }
        if (character_in_line > 0)
        {
            rows++;
            count += character_in_line;
        }
        
    }
    if (rows * rows != count){
        printf("Error, Matriks harus berbentuk persegi (baris = kolom)\n");
        fclose(file);
        return 1;
    }
    
    n = rows;

    rewind(file);//muat file dari baris awal
    char **grid = (char **)malloc(n * sizeof(char *)); 
    for (int i = 0; i < n; i++)
    {
        grid[i] = (char *)malloc(n * sizeof(char));
    }
    
    int *q = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(file, " %c", &grid[i][j]);//memasukkan isi dari file ke grid
        }
        q[i] = i; //inisialisasi queen awal dengan indeks array sebagai baris, dan nilai array sebagai kolom
    }
    fclose(file);

    printf("Mencari solusi untuk persoalan Queens secara Brute Force...\n\n");
    clock_t start_time = clock();
    unsigned long long attempts = 0;
    bool found = false;

    do
    {
        attempts++;
        if (attempts % 1000 == 0) //live update setiap 1000 percobaan
        {
            printf("percobaan ke %llu : \n", attempts);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (q[i] == j){
                        printf("#");
                    }else{
                        printf("%c", grid[i][j]);
                    }
                    
                }
                printf("\n");
            }
            printf("\n");
        }
        
        if (isValid(q, n, grid))
        {
            found = true;
            break;
        }
        
    } while (nextPerm(q, n)); //mencoba percobaan berikutnya jika masih valid
    
    clock_t end_time = clock();
    double time = ((double)(end_time - start_time)* 1000)/CLOCKS_PER_SEC;
    if (found)
    {
        printf("Solusi ditemukan : \n");
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (q[i] == j){
                    printf("#");
                }else{
                    printf("%c", grid[i][j]);
                }
                
            }
            printf("\n");
        }
        char pilihan[10];
        printf("Waktu pencarian : %.2f ms\n", time);
        printf("Banyak kasus yang ditinjau : %llu kasus\n", attempts);
        printf("Apakah Anda ingin menyimpan solusi? (Ya/Tidak) ");
        scanf("%s", pilihan);
        if (strcmp(pilihan, "Ya") == 0)
        {
            char nama_file_solusi[100];
            char path[150];
            printf("Masukkan nama file solusi : ");
            scanf("%s", nama_file_solusi);

            sprintf(path, "test/%s", nama_file_solusi);

            FILE *solusi = fopen(path, "w");
            if (solusi == NULL)
            {
                printf("Gagal menyimpan, pastikan folder sudah tersedia\n");
            }else{
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++){
                        if (q[i] == j){
                            fprintf(solusi,"#");
                        }else{
                            fprintf(solusi, "%c", grid[i][j]);
                        }
                    }
                    fprintf(solusi, "\n");
                }
                fclose(solusi);
                printf("Solusi berhasil disimpan di %s\n", path);
            }
            
        }else if (strcmp(pilihan, "Tidak") == 0){
            printf("Solusi tidak disimpan\n");
        }else{
            printf("input tidak valid\n");
        }
    }else{
        printf("Tidak ada solusi\n");
    }
    
    for (int i = 0; i < n; i++)
    {
        free(grid[i]);
    }
    free(grid);
    free(q);
    return 0;
}