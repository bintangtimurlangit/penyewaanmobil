#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "PPM_UAS_Algo.h"

struct listNode {
  char nopol[100];
  int id;
  char mobil[100];
  char lokasi[100];
  char ketersediaan[100];
  int hargaAkhir;
  int jumlahDeposito;
  int harga;
  int minuteIn;
  int hourIn;
  int denda;
  struct listNode *rightPtr;
  struct listNode *leftPtr;
};

typedef struct listNode ListNode; 
typedef ListNode *ListNodePtr;

void menu(ListNodePtr *headPtr, ListNodePtr *tailPtr, ListNodePtr *pricePtr, int *idMobil);
void listMenu();
void sortDataAsc(ListNodePtr headPtr);
void sortDataDesc(ListNodePtr headPtr);
void addQueue(ListNodePtr *headPtr, char nopol[100], char mobil[100], char lokasi[100], int harga, char ketersediaan[100], int *idMobil, int temp);
int isEmpty (ListNodePtr headPtr);
void printQueue(ListNodePtr currentPtr);

void searchMobil(ListNodePtr *headPtr);
void searchLokasi(ListNodePtr *headPtr);
void searchKetersediaan(ListNodePtr *headPtr);
void searchID(ListNodePtr *headPtr, int idMobil, int *search_toggle, char *mobil_found, char *status_toggle);
void prosesID(ListNodePtr *headPtr, int idMobil, int proses, int hariPeminjaman, int hargaAkhir, int jumlahDeposito, int hourIn, int minuteIn);
void prosesMobil(ListNodePtr *headPtr, char mobil_found[100], int proses, int hariPeminjaman, int hargaAkhir, int jumlahDeposito, int hourIn, int minuteIn);
void prosesHarga(ListNodePtr *headPtr, int harga_found, int proses, int hariPeminjaman, int hargaAkhir, int jumlahDeposito, int hourIn, int minuteIn);

void errorinput();
void menuPetunjuk();
void exitProg();

int nomorId;

int main(void){
	system("color 70");	//Ubah Background Terminal
	ListNodePtr headPtr = NULL;
	ListNodePtr tailPtr = NULL;
	ListNodePtr pricePtr = NULL;
	int i, idMobil;
	
	FILE * fileDataMobil;
	FILE * fileDataPembayaran;
	FILE * fileDataPeminjaman;
	
	system("cls");
	printf("\n\n\n");
	printf("\t\t========================================\n"); 
	printf("\t\t\t\t\t\t\t\tProgram ini dibuat oleh: \n\n");
	printf("\t\t\t\t\t\t\t\tBintang Timurlangit\n");
	printf("\t\t\tProgram Penyewaan Mobil ");
	printf("\t\tKhesar Kurniawan \n");
	printf("\t\t\t\t\t\t\t\tMahdi Husein Punca \n");
	printf("\t\t\t\t\t\t\t\tRaqqat Amarasangga I\n");
	printf("\t\t\t\t\t\t\t\tSinung Agung Cahyono\n");
	printf("\t\t========================================\n\n\n");
	printf("\n\n\n\n\n\n\t\t\t\t\t\t  Program Loading...\n\n");
	printf("\t\t\t\t");
	
	for(i = 0; i < 50; i++) { //print program loading awal untuk keperluan user friendly
		printf("=");
	  	Sleep(1); //delay dalam 15 ms, nanti "=" print 1 per 1 hingaa 50 kali
 	} 
 	
 	Sleep(1000); //delay dalam ms (2 sekon)
 	printf("\n\n");
 	
	menu(&headPtr, &tailPtr, &pricePtr, &idMobil);
	return 0;
}

void menu(ListNodePtr *headPtr, ListNodePtr *tailPtr, ListNodePtr *pricePtr, int *idMobil){
	int proses, caraSort;
	char password[55];
	char nopol[100], mobil[100], lokasi[100], ketersediaan[100], search_mobil[100], search_lokasi[100];
	int harga;
	int input_id;
	int tempSort, inputSort, inputMenu, inputSearch, search_toggle, harga_found;
	char yesorno[10], status_toggle[100], mobil_found[100], masih[100], lanjutBayar[100], ketersediaan_toggle[100];
	
	char namaPemesan[100];
	int nomorId, hariAwalPeminjaman, hariAkhirPeminjaman, bulanAwalPeminjaman, bulanAkhirPeminjaman, tahunAwalPeminjaman, tahunAkhirPeminjaman;
	int hargaAkhir, jumlahDeposito, hariPeminjaman, monthToDate, yearToDate;
	int hourIn, minuteIn;
	char *ptrMobil_found = mobil_found;
	char *ptrStatus_toggle = status_toggle;
	
	system("cls");
	listMenu();
	printf("\t\tPilih Menu => ");
	scanf("%d", &inputMenu); //meminta masukkan input menu
	
	while(inputMenu >= 1 && inputMenu <= 8){
		switch(inputMenu){
			case 1:
				system("cls");
				printf("\n\n\t\t\t\t\t\tList Mobil");
				printf("\n\n\n\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
				printf("\t================================================================================================\n\n");
				sortDataAsc(*tailPtr); //Display List Mobil yang di sorting berdasarkan ID secara Ascending
				break;
			
			case 2:
				strcpy(masih, "ya");
				system("cls");
				printf("\n\n\n\n\t\t\t\t\t==================================\n\n");
				printf("\t\t\t\t\tTekan Enter Untuk Melanjutkan ");
			    int p = 0;
			    
			    printf("\n\n\t\t\t\t\t==================================\n\n");
			    if(!stricmp(password,"")){ 
			  		system("cls");
			  		while(strcmp(masih, "0") != 0){
						printf("\n\n\n\t\t\t MENU INPUT MOBIL \n");
					
                        do{
						    printf("\n\n  Input Nama Mobil\t\t    : ");
						    scanf(" %[^\n]s", &mobil);	
					    } while(strlen(mobil) > 20); //Input Nama mobil tidak lebih dari 20 karakter
				
					    do{
						    printf("  Input Nomor Polisi Mobil\t    : ");
						    scanf(" %[^\n]s", &nopol);
						    strupr(nopol);	
						    if(strlen(nopol) > 10){
								printf("  Input Nomor Polisi Maksimal 10 Karakter\n\n");
							}
					    } while(strlen(nopol) > 10); //Input Nomor Polisi tidak lebih dari 10 karakter
						
					    do{
						    printf("  Input Lokasi Penyewaan Mobil\t    : ");
						    scanf(" %[^\n]s", &lokasi);	
						    strcpy(ketersediaan, "Tersedia");
					    } while(strlen(lokasi) > 20); //Input Lokasi Station tidak lebih dari 20 karakter
						
					    printf("  Input Harga Mobil per-Hari\t    : ");
					    scanf("%d", &harga); //Input Harga Mobil
						
					    printf("  Status Ketersediaan Mobil\t    : %s\n\n", ketersediaan); //Print ketersediaan Mobil
						
					    addQueue(headPtr, nopol, mobil, lokasi, harga, ketersediaan, idMobil, tempSort = 1); //Masukkan data data mobil menuju fungsi addQueue, tempSort = 1 untuk list 1
					    addQueue(tailPtr, nopol, mobil, lokasi, harga, ketersediaan, idMobil, tempSort = 2); //Masukkan data data mobil menuju fungsi addQueue, tempSort = 2 untuk list 2
					    addQueue(pricePtr, nopol, mobil, lokasi, harga, ketersediaan, idMobil, tempSort = 3); //Masukkan data data mobil menuju fungsi addQueue, tempSort = 3 untuk List 3
					
		 		    	*idMobil = *idMobil + 1;	
		 		    	system("pause");
		 		    	system("cls");
		 		    	
		 		    	printf("  Data mobil %s dengan nomor polisi %s telah berhasil disimpan\n\n", &mobil, &nopol);
		 		    	printf("  Ingin menginput lagi? \n  (tekan 0 untuk selesai || lainnya anda bisa menginput lagi) = ");
		 		    	scanf("%s", &masih);
		 		    	strlwr(masih); //lowercase
		 		    	system("cls");
					}
				}
			 	else{
					printf("\\nSilahkan masuk ke menu lainnya!!\n\n\n");	
				}
				
				break;
			
			case 3:
				system("cls");
				printf("\t\t\t\t====================================================\n\n");
				printf("\t\t\t\t\t\tMenu Sorting\n\n");
				printf("\t\t\t\t====================================================\n\n");
				printf("\tPilih Fitur Sorting Berdasarkan: \n");
				printf("\t[pilih 0 untuk kembali]\n\n");
				printf("\t1. Sorting Berdasarkan ID Mobil\n");
				printf("\t2. Sorting Berdasarkan Nama Mobil\n");
				printf("\t3. Sorting Berdasarkan Harga Mobil\n");
				printf("\n\tPilih Fitur Sorting => ");
				scanf("%d", &inputSort); //input menu sorting berdasarkan 3 metode
				switch(inputSort){
					case 0:
						system("cls");
						listMenu();
						break;
					
					case 1: //berdasarkan ID
						system("cls");
						printf("\tSorting Dilakukan Berdasarkan ID Mobil: \n");
						printf("\t[tekan 0 untuk kembali]\n\n");
						printf("\t  1. Ascending\n");
						printf("\t  2. Descending\n");
						printf("\t  Input Cara Sorting => ");
						scanf("%d", &caraSort);
						
						switch(caraSort){
							case 1: //secara Ascending
								printf("\t\t\t\t   List Mobil \n\n");
								printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
								printf("\t================================================================================================\n\n");
								sortDataAsc(*tailPtr);	
								printf("\n\n");
								break;
							
							case 2: //secara Descending
								printf("\t\t\t\t   List Mobil \n\n");
								printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
								printf("\t================================================================================================\n\n");
								sortDataDesc(*tailPtr);	
								printf("\n\n");
								break;
						}
						system("pause");
						system("cls");
						break;
						
					case 2: //Berdasarkan nama mobil
						system("cls");
						printf("Sorting Dilakukan Berdasarkan Nama Mobil: \n");
						printf("[tekan 0 untuk kembali]\n\n");
						printf("  1. Ascending\n");
						printf("  2. Descending\n");
						printf("  Input Cara Sorting => ");
						scanf("%d", &caraSort);
						
						switch(caraSort){
							case 1: //secara ascending
								printf("\t\t\t\t   List Mobil \n\n");
								printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
								printf("\t================================================================================================\n\n");
								sortDataAsc(*headPtr);	
								printf("\n\n");
								break;
							
							case 2: //secara descending
								printf("\t\t\t\t   List Mobil \n\n");
								printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
								printf("\t================================================================================================\n\n");
								sortDataDesc(*headPtr);	
								printf("\n\n");
								break;
						}
						system("pause");
						system("cls");
						break;
						
					case 3: //sorting berdasarkan harga sewa
						system("cls");
						printf("Sorting Dilakukan Berdasarkan Harga Sewa Mobil: \n");
						printf("[tekan 0 untuk kembali]\n\n");
						printf("  1. Ascending\n");
						printf("  2. Descending\n");
						printf("  Input Cara Sorting => ");
						scanf("%d", &caraSort);
						
						switch(caraSort){
							case 1: //secara ascending
								printf("\t\t\t\t   List Mobil \n\n");
								printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
								printf("\t================================================================================================\n\n");
								sortDataAsc(*pricePtr);	
								printf("\n\n");
								break;
							
							case 2: //secara descending
								printf("\t\t\t\t   List Mobil \n\n");
								printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
								printf("\t================================================================================================\n\n");
								sortDataDesc(*pricePtr);	
								printf("\n\n");
								break;
						}
						system("pause");
						system("cls");
						break;
					
					default:
						errorinput();
						printf("\t\tMasukkan input dari 1 hingga 3 saja\n");
						system("pause");
						system("cls");
						listMenu(); //kembali ke menu pencarian data
				}
				break;
			
			case 4:
				system("cls");
				printf("\t\t\t\t====================================================\n\n");
				printf("\t\t\t\t\t\tMenu Searching\n\n");
				printf("\t\t\t\t====================================================\n\n");
				printf("\tPilih Fitur Searching Berdasarkan: \n");
				printf("\t[pilih 0 untuk kembali]\n\n");
				printf("\t1. Nama Mobil\n");
				printf("\t2. Lokasi Station\n");
				printf("\t3. Ketersediaan\n");
				printf("\n\tPilih Fitur Search => ");
				scanf("%d", &inputSearch); //memilih searching yang dilakukan
				
				switch(inputSearch){
					//ingin kembali ke menu utama
					case 0:
						system("cls");
						listMenu();
						break;
					
					//mencari berdasarkan mobil
					case 1:
						searchMobil(headPtr);
						system("pause");
						system("cls");
						break;
					
					//mencari berdasarkan lokasi	
					case 2:
						searchLokasi(headPtr);
						system("pause");
						system("cls");
						break;
						
					case 3:
						searchKetersediaan(headPtr);
						system("pause");
						system("cls");
						break;
					
					default:
						errorinput();
						printf("\t\tMasukkan input dari 1 hingga 3 saja\n");
						system("pause");
						system("cls");
						listMenu(); //kembali ke menu pencarian data
				}
				break;
				
			case 5:
				system("cls");
				printf("\t\t\t\t   List Mobil \n\n");
				printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
				printf("\t================================================================================================\n\n");
				sortDataAsc(*tailPtr);
				
				printf("\n\n\t --- PEMESANAN MOBIL --- \n\n");
			    printf("\tMasukkan ID mobil: ");
			    scanf("%d", &input_id);
			    searchID(tailPtr, input_id, &search_toggle, ptrMobil_found, ptrStatus_toggle); //mencari id yang sesuai dengan yang ingin dipesan
			    if (search_toggle == 1){
			    	printf("\nMobil Ada di Database\n");
			    	if (stricmp(status_toggle, "Tersedia") == 0){
			    		while(1){
				    		printf("Apakah anda yakin ingin menyewa Mobil ini? (Y/N) ");
				        	scanf("%s", yesorno);
				        	strupr(yesorno);
				        	if (strcmp(yesorno,"Y")==0){
				        		system("cls");
				        		printf("\n\n\t\t\t\t====================================================\n\n");
								printf("\t\t\t\t\t\tMenu Pembayaran\n\n");
								printf("\t\t\t\t====================================================\n\n");
									
								//print mobil yang anda pilih
								printf("\tMobil yang telah Anda Pesan: \n");
								searchID(tailPtr, input_id, &search_toggle, ptrMobil_found, ptrStatus_toggle); //mencari id yang sesuai dengan yang ingin dipesan
								
								printf("\n\n  Masukkan Data Diri Anda: \n\n"); //input data diri penyewa mobil
								printf("\tNama\t\t\t\t   : "); 
								scanf(" %[^\n]s", &namaPemesan); 
								printf("\tNomor Identitas\t\t\t   : ");
								scanf("%d", &nomorId);
								do{
									printf("\tTanggal Awal Peminjaman (dd/mm/yy) : ");
									scanf("%d/%d/%d", &hariAwalPeminjaman, &bulanAwalPeminjaman, &tahunAwalPeminjaman); //input hari bulan dan tahun awal
									if(hariAwalPeminjaman > 30 || hariAwalPeminjaman < 0 || bulanAwalPeminjaman > 12 || bulanAwalPeminjaman < 0){ //jika hari lebih dari 30 dan bulan lebih dari 12
										printf("  Input Hari kurang dari 30 dan Bulan kurang dari 12\n\n");
									}	
								} while(hariAwalPeminjaman > 30 || hariAwalPeminjaman < 0 || bulanAwalPeminjaman > 12 || bulanAwalPeminjaman < 0);
								
								do{
									printf("\tTanggal Akhir Peminjaman (dd/mm/yy) : ");
									scanf("%d/%d/%d", &hariAkhirPeminjaman, &bulanAkhirPeminjaman, &tahunAkhirPeminjaman);
									if(hariAkhirPeminjaman > 30 || hariAkhirPeminjaman < 0 || bulanAkhirPeminjaman > 12 || bulanAkhirPeminjaman < 0){
										printf("  Input Hari kurang dari 30 dan Bulan kurang dari 12\n\n");
									}	
								} while(hariAkhirPeminjaman > 30 || hariAkhirPeminjaman < 0 || bulanAkhirPeminjaman > 12 || bulanAkhirPeminjaman < 0);
								
								monthToDate = (bulanAkhirPeminjaman - bulanAwalPeminjaman)*30; //bulan akhir - bulan awal = bulan
								yearToDate = (tahunAkhirPeminjaman - tahunAwalPeminjaman)*365; //tahun akhir - tahun awal = tahun
								hariPeminjaman = hariAkhirPeminjaman - hariAwalPeminjaman + monthToDate + yearToDate; //hari total = hari akhir - hari awal + bulan + tahun
								
								proses = 1;
				        		prosesID(tailPtr, input_id, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn); //proses untuk list ID
				        		prosesMobil(headPtr, mobil_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn); //proses untuk list Mobil
				        		prosesHarga(pricePtr, harga_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn); //proses untuk harga mobil
				        		printf("\n\t\t\t\t\t\t== Mobil berhasil disewa ==\n\n\n");

				            	break;
				        	}
				          	else if (strcmp(yesorno,"N")==0){
				            	printf("\n\t\t\t\t== Mobil tidak berhasil disewa ==\n");
				            	break;
				          	}
				          	else{
				            	errorinput();
				            	continue;
				          	}
			        	}
			    	}
			   		else {
			    		printf("\n\t\t\t\t\t Maaf, Mobil telah disewakan\n");
			    	}
			    }
			    else{
			      	printf("\n\t\t\t\t\t== Mobil dengan ID %d Tidak ditemukan==\n", &input_id);
			    }
			break;
			
			case 6:
				system("cls");
				printf("\n\n\n\n\t\t\t\t=================================================\n");
				printf("\n\t\t\t\tPengembalian Mobil Pada Pukul (Jam:Menit) : ");
				scanf("%d:%d", &hourIn, &minuteIn); //input jam dan menit ketika operator menggunakan program
				printf("\n\n\n\n\t\t\t\t\t\tList Mobil \n\n");
				printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
				printf("\t================================================================================================\n\n");
				sortDataAsc(*tailPtr);
				printf("\n\n\n\t\t\t\t\t --- Pengembalian Mobil Mobil --- \n\n");
			    printf("\tMasukkan ID mobil: ");
			    scanf("%d", &input_id);
			    searchID(tailPtr, input_id, &search_toggle, ptrMobil_found, ptrStatus_toggle); //mencari id yang sesuai dengan yang ingin dipesan
			    if (search_toggle == 1){ 
			    	printf("\nMobil Ada di Database\n");
			    	if (stricmp(status_toggle, "Tidak Tersedia") == 0){
			    		while(1){
				    		printf("Apakah anda yakin ingin mengembalikan mobil ini? (Y/N) ");
				        	scanf("%s", yesorno);
				        	strupr(yesorno);
				        	if (strcmp(yesorno,"Y")==0){
				        		system("cls");
				        		printf("\n\n\t\t\t\t====================================================\n\n");
								printf("\t\t\t\t\t\tMenu Pengembalian Mobil\n\n");
								printf("\t\t\t\t====================================================\n\n");
									
								//print mobil yang anda pilih
								printf("\tMobil yang telah Anda ingin Kembalikan: \n");
								searchID(tailPtr, input_id, &search_toggle, ptrMobil_found, ptrStatus_toggle); //mencari id yang sesuai dengan yang ingin dipesan	
								
								proses = 2;
				        		prosesID(tailPtr, input_id, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn); //proses untuk list ID
				        		prosesMobil(headPtr, mobil_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn); //proses untuk list mobil
				        		prosesHarga(pricePtr, harga_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn); //proses untuk list harga
				        		printf("\n\t\t\t\t\t\t== Mobil berhasil dikembalikan ==\n");
				            	break;
				        	}
				          	else if (strcmp(yesorno,"N")==0){
				            	printf("\n\t\t\t\t== Mobil tidak berhasil dikembalikan ==\n");
				            	break;
				          	}
				          	else{
				            	errorinput();
				            	continue;
				          	}
			        	}
			    	}
			   		else {
			    		printf("\n\t\t\t\t\tMaaf, Mobil sedang dipinjam\n");
			    	}
			    }
			    else{
			      	printf("\n\t\t\t\t\t== Mobil tidak ditemukan ==\n");
			    }
			break;
			
			case 7:
				system("cls");
				menuPetunjuk();
				break;
				
			case 8:
				exitProg();
				system("pause");
				system("cls");
				break;
			
			default:
				printf("Input Salah, Harap masukkan kembali\n\n");
			    system("pause");
			    system("cls");
			    break;
		}
		system("pause");
		system("cls");
		
		listMenu();
		printf("\n  Input Menu = ");
		scanf("%d", &inputMenu);	
	}
}

void addQueue(ListNodePtr *headPtr, char nopol[100], char mobil[100], char lokasi[100], int harga, char ketersediaan[100], int *idMobil, int temp){
	nomorId = *idMobil + 1;
	
	if(*headPtr == NULL){
		*headPtr = (ListNode*)malloc(sizeof(ListNode)); //membuat memory allocation
		
		if(*headPtr != NULL){ //memindahkan data yang telah diinput oleh user menuju ke struct
			(*headPtr)->id = nomorId; //passing nomor ID
			strcpy((*headPtr)->mobil, mobil); //passing nama mobil
			strcpy((*headPtr)->nopol, nopol); //passing nopol
			strcpy((*headPtr)->lokasi, lokasi); //passing lokasi
			(*headPtr)->harga = harga; //passing harga
			strcpy((*headPtr)->ketersediaan, ketersediaan); //passing ketersediaan
			
			(*headPtr)->rightPtr = NULL;
			(*headPtr)->leftPtr = NULL;
			
		} else {
			printf("%s is not inserted. No Memory available.\n", mobil);
			printf("%s is not inserted. No Memory available.\n", nopol);
			printf("%s is not inserted. No Memory available.\n", lokasi);
			printf("%d is not inserted. No Memory available.\n", harga);
			printf("%s is not inserted. No Memory available.\n", ketersediaan);
		}	
	} else {
		if(temp == 1){ //untuk list ID
			if(stricmp(mobil, (*headPtr)->mobil) < 0){
				addQueue(&((*headPtr)->leftPtr), nopol, mobil, lokasi, harga, ketersediaan, idMobil, temp); //memasukkan data ke leftPtr karena kurang dari 
			} else if(stricmp(mobil, (*headPtr)->mobil) > 0){
				addQueue(&((*headPtr)->rightPtr), nopol, mobil, lokasi, harga, ketersediaan, idMobil, temp); //memasukkan data ke rightPtr karena lebih dari
			} else {
				printf("\n\tPerhatian, mobil dengan nama yang sama sudah ada!\n");
			}	
		} else if (temp == 2){ //untuk List Mobil
			if(nomorId < (*headPtr)->id){
				addQueue(&((*headPtr)->leftPtr), nopol, mobil, lokasi, harga, ketersediaan, idMobil, temp); //memasukkan data ke leftPtr karena kurang dari 
			} else if(nomorId > (*headPtr)->id){
				addQueue(&((*headPtr)->rightPtr), nopol, mobil, lokasi, harga, ketersediaan, idMobil, temp); //memasukkan data ke rightPtr karena lebih dari
			} else {
				printf("\n\tID mobil sudah diinput!\n");
			}
		} else if (temp == 3){ //untuk List Harga
			if(harga < (*headPtr)->harga){
				addQueue(&((*headPtr)->leftPtr), nopol, mobil, lokasi, harga, ketersediaan, idMobil, temp); //memasukkan data ke leftPtr karena kurang dari 
			} else if(harga > (*headPtr)->harga){
				addQueue(&((*headPtr)->rightPtr), nopol, mobil, lokasi, harga, ketersediaan, idMobil, temp); //memasukkan data ke rightPtr karena lebih dari
			} else { 
				printf("\n\tMobil dengan Harga tersebut sudah dimasukkan\n");
			}
		}
	}
}

void sortDataAsc(ListNodePtr headPtr){ //secara ascending
  if(headPtr != NULL){
    sortDataAsc(headPtr->leftPtr); //masukkan data ke LeftPtr
	printf("\t%2d |", headPtr->id);
    printf("%20s |", headPtr->mobil);
    printf("%13s |", headPtr->nopol);
    printf("%17s |", headPtr->lokasi);
    printf("  Rp.%10d |", headPtr->harga);
    printf("%14s ", headPtr->ketersediaan);
    printf("\n");
    sortDataAsc(headPtr->rightPtr); //masukkan data ke rightPtr
  }
}

void sortDataDesc(ListNodePtr headPtr){ //secara descending
  if(headPtr != NULL){
    sortDataDesc(headPtr->rightPtr); //masukkan data ke rightPtr
	printf("\t%2d |", headPtr->id);
    printf("%20s |", headPtr->mobil);
    printf("%13s |", headPtr->nopol);
    printf("%17s |", headPtr->lokasi);
    printf("  Rp.%10d |", headPtr->harga);
    printf("%14s ", headPtr->ketersediaan);
    printf("\n");
    sortDataDesc(headPtr->leftPtr); //masukkan data ke LeftPtr
  }
}

void searchMobil(ListNodePtr *headPtr){					//Fungsi untuk mencari kontak tertentu berdasarkan nama
	char search_mobil[25];
	char *found, *found1;
	int loop, flag;
	
	ListNode *search;
    search = (ListNode*)malloc(sizeof(ListNode)); 
    search = *headPtr;
    
	
	printf("   Input Nama Mobil yang ingin dicari: ");
	scanf(" %[^\n]s", &search_mobil); //input nama mobil yang ingin disearching
    
    if (search == NULL){
    	printf("\n		DATABASE IS EMPTY.\n");		//If the head is NULL hence the database is empty
	}else{    
		while(search != NULL){						//If the head is not NULL hence the program will traverse all nodes
	    	found = stristr(search->mobil, search_mobil);
	    	
			if(found){
				if (loop == 0){
					printf("\t\t\t\t   List Mobil Berdasarkan Search Nama Mobil \n\n");
					printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
					printf("\t================================================================================================\n\n");
					flag = 1;
					loop++;
				}
				printf("\t%2d |", search->id);
				printf("%20s |", search->mobil);
			    printf("%13s |", search->nopol);
			    printf("%17s |", search->lokasi);
			    printf("  Rp.%10d |", search->harga);
			    printf("%14s ", search->ketersediaan);
			    printf("\n");
			}
			//bagian stricmp tetap digunakan untuk melihat kondisi address sebelum dan sesudah dilakukan stristr
			if(stricmp(search_mobil, search->mobil) < 0){//saat terlihat yang kurang dari input yang kita punya
				search = search->leftPtr;	//diletakkan disebelah kiri (akan lebih dulu)
			} else if(stricmp(search_mobil, search->mobil) > 0){ //saat hasil yang diperoleh ada setelah input
				search = search->rightPtr;	//diletakkan sebelah kiri (akan tertampil setelah bagian awal terpenuhi)
			} else if(stricmp(search_mobil, search->mobil) == 0){ //error handling saat ditemukan sama
				search = search->leftPtr;//akan berhenti di leftPtr dan tidak looping ke bagian kanan yang tidak berujung
			}
		}
		
		if(found == NULL){							//If the substring wasn't found in the string
			if (flag == 0)
				printf("\n		%s NOT FOUND!\n", search_mobil);
		}
	}
}

void searchLokasi(ListNodePtr *headPtr){					//Fungsi untuk mencari kontak tertentu berdasarkan nama
	char search_lokasi[25];
	char *found, *found1;
	int loop, flag;
	
	ListNode *search;
    search = (ListNode*)malloc(sizeof(ListNode)); 
    search = *headPtr;
	
	printf("   Input Lokasi Mobil yang ingin dicari: ");
	scanf(" %[^\n]s", &search_lokasi); //input nama mobil yang ingin disearching
    
    if (search == NULL){
    	printf("\n		DATABASE IS EMPTY.\n");		//If the head is NULL hence the database is empty
	}else{    
		while(search != NULL){						//If the head is not NULL hence the program will traverse all nodes
	    	found = stristr(search->lokasi, search_lokasi);
	    	
			if(found){ //setiap found akan dilakukan pencarian 1 per satu 
				if (loop == 0){
					printf("\t\t\t\t   List Mobil Berdasarkan Search Lokasi \n\n");
					printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
					printf("\t================================================================================================\n\n");
					flag = 1;
					loop++;
				}
				printf("\t%2d |", search->id); //2 hasil teratas akan diprint
				printf("%20s |", search->mobil);
			    printf("%13s |", search->nopol);
			    printf("%17s |", search->lokasi);
			    printf("  Rp.%10d |", search->harga);
			    printf("%14s ", search->ketersediaan);
			    printf("\n");
			}
			//bagian stricmp tetap digunakan untuk melihat kondisi address sebelum dan sesudah dilakukan stristr
			if(stricmp(search_lokasi, search->lokasi) < 0){ //saat terlihat yang kurang dari input yang kita punya
				search = search->leftPtr;	//diletakkan disebelah kiri (akan lebih dulu)
			} else if(stricmp(search_lokasi, search->lokasi) > 0){ //saat hasil yang diperoleh ada setelah input
				search = search->rightPtr;	//diletakkan sebelah kiri (akan tertampil setelah bagian awal terpenuhi)
			} else if(stricmp(search_lokasi, search->lokasi) == 0){ //error handling saat ditemukan sama
				search = search->leftPtr; //akan berhenti di leftPtr dan tidak looping ke bagian kanan yang tidak berujung
			}
				//Move to the next node iteration
		}
		
		if(found == NULL){							//If the substring wasn't found in the string
			if (flag == 0)
				printf("\n		%s NOT FOUND!\n", search_lokasi);
		}
	}
}

void searchKetersediaan(ListNodePtr *headPtr){					//Fungsi untuk mencari kontak tertentu berdasarkan nama
	char search_ketersediaan[25];
	int *found;
	int loop, flag, cariAvail;
	
	ListNode *search;
    search = (ListNode*)malloc(sizeof(ListNode)); 
    search = *headPtr;
	
	printf("\tSearch Ketersediaan Mobil \n\t[1. Tersedia || 2. Tidak Tersedia]\n");
	printf("\tinput ketersediaan -> ");
	scanf(" %d", &cariAvail);
	
    if(cariAvail == 1){
		strcpy(search_ketersediaan, "Tersedia");
	} else if(cariAvail == 2){
		strcpy(search_ketersediaan, "Tidak Tersedia");
	} else{
		system("cls");
		listMenu();
	}
	
    if (search == NULL){
    	printf("\n		DATABASE IS EMPTY.\n");		//If the head is NULL hence the database is empty
	} else{    
		while(search != NULL){						//If the head is not NULL hence the program will traverse all nodes
			if(stricmp(search->ketersediaan, search_ketersediaan) == 0){ //setiap found akan dilakukan pencarian 1 per satu 
				if (loop == 0){
					printf("\t\t\t\t   List Mobil Berdasarkan Search Lokasi \n\n");
					printf("\tID |\t Nama Mobil\t | Nomor Polisi |      Lokasi      |   Harga Sewa   |      Ketersediaan\n");
					printf("\t================================================================================================\n\n");
					flag = 1;
					loop++;
				}
				printf("\t%2d |", search->id); //2 hasil teratas akan diprint
				printf("%20s |", search->mobil);
			    printf("%13s |", search->nopol);
			    printf("%17s |", search->lokasi);
			    printf("  Rp.%10d |", search->harga);
			    printf("%14s ", search->ketersediaan);
			    printf("\n");
			      
			} search = search->rightPtr;
				//Move to the next node iteration
		}
		
		if(found == NULL){							//If the substring wasn't found in the string
			if (flag == 0)
				printf("\n		%s NOT FOUND!\n", search_ketersediaan);
		}
	}
}

void searchID(ListNodePtr *headPtr, int idMobil, int *search_toggle, char *mobil_found, char *status_toggle){
	if(*headPtr != NULL){
		if(idMobil < (*headPtr)->id){
			searchID(&((*headPtr)->leftPtr), idMobil, search_toggle, mobil_found, status_toggle); //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di leftPtr
		} else if(idMobil > (*headPtr)->id){
			searchID(&((*headPtr)->rightPtr), idMobil, search_toggle, mobil_found, status_toggle); //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di rightPtr
		} else if(idMobil == (*headPtr)->id){ //data akan dibandingkan jika nama mobil yang diinput sama 
			printf("\t%2d |", (*headPtr)->id);
			printf("%20s |", (*headPtr)->mobil);
		    printf("%13s |", (*headPtr)->nopol);
		    printf("%17s |", (*headPtr)->lokasi);
		    printf("  Rp.%10d |", (*headPtr)->harga);
		    printf("%14s ", (*headPtr)->ketersediaan);
		    *search_toggle = 1;
		    strcpy(mobil_found,(*headPtr)->mobil);
      		strcpy(status_toggle,(*headPtr)->ketersediaan);
		    printf("\n");
		} else {
			printf("\n\n\t\t\t\tTidak ada mobil dengan ID yang anda masukkan!\n\n");
		}
	} 
}

void prosesMobil(ListNodePtr *headPtr, char mobil_found[100], int proses, int hariPeminjaman, int hargaAkhir, int jumlahDeposito, int hourIn, int minuteIn){
	if(*headPtr != NULL){
		if(stricmp(mobil_found, (*headPtr)->mobil) < 0){ //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di leftPtr
			prosesMobil(&((*headPtr)->leftPtr), mobil_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn);
		} else if(stricmp(mobil_found, (*headPtr)->mobil) > 0){ //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di rightPtr
			prosesMobil(&((*headPtr)->rightPtr), mobil_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn);
		} else if(stricmp(mobil_found, (*headPtr)->mobil) == 0){ //data akan dibandingkan jika nama mobil yang diinput sama 
			if (proses == 1){ //untuk proses 1 atau proses pemesanan mobil
		        strcpy((*headPtr)->ketersediaan, "Tidak Tersedia"); //ketersediaan menjadi tidak tersedia
		        (*headPtr)->hargaAkhir = (*headPtr)->harga * hariPeminjaman; //perhitungan hargaAkhir = harga * durasi pemesanan
		        (*headPtr)->jumlahDeposito = (*headPtr)->hargaAkhir * 0.25; //perhitungan jumlahDeposito
	
		    }
		    else if (proses == 2){ //untuk proses 2 atau proses pengembalian mobil
		    	if(hourIn >= 19 && minuteIn >= 0){ //jika user mengembalikan mobil lebih dari jam operasional yaitu jam 19:00
		    		(*headPtr)->denda = (*headPtr)->jumlahDeposito * 0.2 * (hourIn - 19); //perhitungan denda
		    		(*headPtr)->jumlahDeposito = (*headPtr)->jumlahDeposito - (*headPtr)->denda; //perhitungan jumlah deposito yang akan dikembalikan
					strcpy((*headPtr)->ketersediaan, "Tersedia"); //ketersediaan menjadi tersedia
					
					} else {
					strcpy((*headPtr)->ketersediaan, "Tersedia"); //ketersediaan menjadi tersedia
				}
		    }
		}
	} 
}

void prosesHarga(ListNodePtr *headPtr, int harga_found, int proses, int hariPeminjaman, int hargaAkhir, int jumlahDeposito, int hourIn, int minuteIn){
	if(*headPtr != NULL){
		if(harga_found < (*headPtr)->harga){ //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di leftPtr
			prosesHarga(&((*headPtr)->leftPtr), harga_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn);
		} else if(harga_found > (*headPtr)->harga){ //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di rigthPtr
			prosesHarga(&((*headPtr)->rightPtr), harga_found, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn);
		} else if(harga_found == (*headPtr)->harga){ //data akan dibandingkan jika nama mobil yang diinput sama 
			if (proses==1){ //untuk proses 1 atau proses pemesanan mobil
		        strcpy((*headPtr)->ketersediaan, "Tidak Tersedia"); //ketersediaan menjadi tidak tersedia
		        (*headPtr)->hargaAkhir = (*headPtr)->harga * hariPeminjaman; //perhitungan hargaAkhir = harga * durasi pemesanan
		        (*headPtr)->jumlahDeposito = (*headPtr)->hargaAkhir * 0.25; //perhitungan jumlah Deposito
		    
		    }
		    else if (proses == 2){  //untuk proses 2 atau proses pengembalian mobil
		    	if(hourIn >= 19 && minuteIn >= 0){ //jika user mengembalikan mobil lebih dari jam operasional yaitu jam 19:00
		    		(*headPtr)->denda = (*headPtr)->jumlahDeposito * 0.2 * (hourIn - 19); //perhitungan denda
		    		(*headPtr)->jumlahDeposito = (*headPtr)->jumlahDeposito - (*headPtr)->denda; //perhitungan jumlah deposito yang akan dikembalikan
					strcpy((*headPtr)->ketersediaan, "Tersedia"); //ketersediaan menjadi tersedia
					
				} else {
					strcpy((*headPtr)->ketersediaan, "Tersedia");
					
				}
		    }
		}
	} 
}

void prosesID(ListNodePtr *headPtr, int idMobil, int proses, int hariPeminjaman, int hargaAkhir, int jumlahDeposito, int hourIn, int minuteIn){
	if(*headPtr != NULL){
		if(idMobil < (*headPtr)->id){ //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di leftPtr
			prosesID(&((*headPtr)->leftPtr), idMobil, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn);
		} else if(idMobil > (*headPtr)->id){ //data akan dibandingkan jika nama mobil yang diinput sama dengan yang ada di rightPtr
			prosesID(&((*headPtr)->rightPtr), idMobil, proses, hariPeminjaman, hargaAkhir, jumlahDeposito, hourIn, minuteIn);
		} else if(idMobil == (*headPtr)->id){ //data akan dibandingkan jika nama mobil yang diinput sama 
			if (proses==1){ //untuk proses 1 atau proses pemesanan mobil
		        strcpy((*headPtr)->ketersediaan, "Tidak Tersedia"); //ketersediaan menjadi tidak tersedia
		        (*headPtr)->hargaAkhir = (*headPtr)->harga * hariPeminjaman; //perhitungan hargaAkhir = harga * durasi pemesanan
		        (*headPtr)->jumlahDeposito = (*headPtr)->hargaAkhir * 0.25; //perhitungan jumlahDeposito
		        printf("\tLama Peminjaman		: %d\n", hariPeminjaman);
				printf("\tHarga Akhir		: %d\n", (*headPtr)->hargaAkhir);
				printf("\tBiaya Deposit		: %d\n", (*headPtr)->jumlahDeposito);
		    }
		    else if (proses==2){ //untuk proses 2 atau proses pengembalian mobil
		    	if(hourIn >= 19 && minuteIn >= 0){ //jika user mengembalikan mobil lebih dari jam operasional yaitu jam 19:00
		    		(*headPtr)->denda = (*headPtr)->jumlahDeposito * 0.2 * (hourIn - 19); //perhitungan denda
		    		(*headPtr)->jumlahDeposito = (*headPtr)->jumlahDeposito - (*headPtr)->denda; //perhitungan jumlah deposito yang akan dikembalikan
					strcpy((*headPtr)->ketersediaan, "Tersedia"); //ketersediaan menjadi tersedia
					printf("\n\n\n\t\t\t\tMobil yang ada sewa sudah dikembalikan...\n\n");
					printf("\t\tJumlah Denda = Rp.%d Karena melewati batas waktu operasional sebanyak %d jam\n", (*headPtr)->denda, hourIn - 19);
					printf("\t\t\t  Berikut adalah Deposito yang dikembalikan ke anda = Rp.%d\n\n", (*headPtr)->jumlahDeposito);
				} else {
					strcpy((*headPtr)->ketersediaan, "Tersedia"); //ketersediaan menjadi tersedia
					printf("\n\n\n\t\t\t\tMobil yang ada sewa sudah dikembalikan...\n\n");
					printf("\t\tTidak ada Denda, Karena pengembalian tidak melewati batas waktu operasional!\n");
					printf("\t\t\t  Berikut adalah Deposito yang dikembalikan ke anda = Rp.%d\n\n", (*headPtr)->jumlahDeposito);
				}
		    }
		}
	} 
}

int isEmpty(ListNodePtr headPtr){
	return headPtr == NULL;
}
