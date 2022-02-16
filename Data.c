// Nama		: Wildan Setya Nugraha 
// NIM		: 211511032
// Kelas	: 1A - D3 T.Informatika
// M.Kuliah	: Struktur Data & Algoritma Praktek 
// Tanggal	: 9 Februari 2022

#include "Data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputData(){
	Data_a *dt;
	int n,i,j;
	FILE *fp;
	system("cls");
	
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n\n");
	
	printf("Masukkan Jumlah Data yang Diinginkan : ");
	scanf("%d", &n);
	
	fp = fopen("File_a.txt","a");

	dt = (Data_a*)calloc(n,sizeof(Data_a));
	
	
	for(i=0;i<n;i++){
		
		fflush(stdin);
		printf("\nKELAS         : ");
		gets(dt[i].kelas);
		strupr(dt[i].kelas); 
		
		fflush(stdin);
		printf("NIM           : ");
		gets(dt[i].NIM);  
			
		fflush(stdin);
		printf("GOL DARAH     : ");
		gets(dt[i].Gol_darah);
		strupr(dt[i].Gol_darah); 
		
		fflush(stdin);
		printf("JENIS KELAMIN : ");
		scanf("%c", &dt[i].jk); 
		dt[i].jk = toupper((dt[i].jk));  

		fwrite(&dt[i], sizeof(Data_a), 1, fp); 
	}
	 
	fclose(fp);
	lanjutkan();
}

void cetakData(){
	Data_a dt;
	FILE *fp;
	
	system("cls");
	
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n");
    printf(" KELAS | NIM       | GOL DARAH | JENIS KELAMIN |\n\n");
    
	if((fp = fopen("File_a.txt","r")) == NULL){
		printf("FILE TIDAK TERSEDIA");
		exit(1);
	}
	while(fread(&dt,sizeof(Data_a),1,fp)){
			printf(" %-6s| %-10s|     %-5s |       %-5c   |\n",dt.kelas,dt.NIM,dt.Gol_darah,dt.jk);
	}
	fclose(fp);
	lanjutkan();
}

void urutkanData(){
	Data_a *dt1, dt2;
	FILE *fp;
	int i,j;
	fp = fopen("File_a.txt","r");
	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(Data_a);
	dt1 = (Data_a*)calloc(n,sizeof(Data_a));
	
	rewind(fp);
	for(i=0; i<n; i++){
		fread(&dt1[i], sizeof(Data_a), 1, fp);
	}
	
	fclose(fp);
	
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(strcmp(dt1[i].Gol_darah, dt1[j].Gol_darah)>0){
				dt2 = dt1[i];
				dt1[i] = dt1[j];
				dt1[j] = dt2;
			}
			
			if(strcmp(dt1[i].Gol_darah, dt1[j].Gol_darah)==0){
				if(dt1[i].jk > dt1[j].jk){
					dt2 = dt1[i];
					dt1[i] = dt1[j];
					dt1[j] = dt2; 
				}
			}
		}
	}
	
	
	fp = fopen("File_a.txt", "w");
	
	system("cls"); 
	
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n");
    printf(" KELAS | NIM       | GOL DARAH | JENIS KELAMIN |\n\n");
    
	
	for(i=0;i<n;i++){
		printf(" %-6s| %-10s|     %-5s |       %-5c   |\n",dt1[i].kelas,dt1[i].NIM,dt1[i].Gol_darah,dt1[i].jk);
		fwrite(&dt1[i], sizeof(Data_a), 1, fp);
	}
	printf("\nDATA BERHASIL DIURUTKAN\n");
	fclose(fp);
	lanjutkan(); 
}

void akumulasiData(){
	Data_a *dt;
	FILE *fp;
	int i,j;
	int Tot_jml_pria, Tot_jml_wanita;
	char var_Gol_darah[3];
	
	fp = fopen("File_a.txt","r");

	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(Data_a);
	dt = (Data_a*)calloc(n,sizeof(Data_a));
	
	rewind(fp);
	for(i=0;i<n;i++){
		fread(&dt[i],sizeof(Data_a),1,fp);
	}
	
	fclose(fp);
	fp = fopen("File_b.txt","w");
	
	system("cls");
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n");
    printf(" GOL DARAH | JML PRIA | JML WANITA |\n\n");
	
	i=0;
	j=0;
	while(i<n){
		Tot_jml_pria = 0;
		Tot_jml_wanita = 0; 
		while(j<n && strcmp(dt[i].Gol_darah,dt[j].Gol_darah)==0){
			if(dt[j].jk == 'P'){
				Tot_jml_pria += 1; 
			} else if(dt[j].jk == 'W'){
				Tot_jml_wanita += 1; 
			}
			j++;
		}
		fprintf(fp,"%s %d %d\n",dt[i].Gol_darah,Tot_jml_pria, Tot_jml_wanita);
		printf("     %-6s|    %-5d |     %-5d  |\n",dt[i].Gol_darah,Tot_jml_pria,Tot_jml_wanita);
		i=j;
	}
	fclose(fp);
	lanjutkan(); 
}

void menu(){
	int ch;
	
		system("cls");
		
		printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n\n");
		printf("                   AKUMULASI GOL DARAH\n");
		printf("                      BY WILDAN SN\n\n");
   		printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    	printf("**********************************************************************************************************************\n");
    
		printf("                      1. Input Data\n");
		printf("                      2. Display\n");
		printf("                      3. Urutkan Data\n");
		printf("                      4. Hitung Data\n");
		printf("                      0. Keluar\n");
		
		printf("\n\nPilihan : ");
		scanf("%d", &ch);
		
		switch(ch){
			case 1:
				inputData();
				break;
			case 2:
				cetakData();
				break;
			case 3:
				urutkanData();
				break;
			case 4:
				akumulasiData();
				break;
		}
	
}

void lanjutkan(){
	
	printf("\n\n\t\t[1] MENU & [0] KELUAR : ");
	switch(getch()){
		case '1':
			menu();
			break;
		case '0':
			break;
		default :
			printf("\n\t\tINPUTAN SALAH (TEKAN ENTER!!)");
			getche();
			lanjutkan(); 	
	}
}


