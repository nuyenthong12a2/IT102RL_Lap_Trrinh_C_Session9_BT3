#include <stdio.h>
#include <string.h>

#define MAX_VE 100

struct VeMayBay {
    char maVe[15];
    char tenHanhKhach[50];
    char hangVe[20];
    float canNangHanhLy;
    double cuocHanhLy;
};

int main() {
    struct VeMayBay danhSachVe[MAX_VE];
    int N;

    // 1. Nhap va kiem tra so luong ve hop le (1 <= N <= 100)
    printf("Nhap so luong ve may bay: ");
    if (scanf("%d", &N) != 1 || N < 1 || N > MAX_VE) {
        printf("Loi: So luong ve khong hop le (yeu cau tu 1 den 100)!\n");
        return 1; // Dung chuong trinh theo yeu cau
    }
    while (getchar() != '\n'); // Don sach bo dem de khong bi troi lenh

    // 2 & 3. Nhap danh sach va tu dong tinh cuoc phi
    for (int i = 0; i < N; i++) {
        printf("\n--- Nhap thong tin ve thu %d ---\n", i + 1);

        printf("Ma ve PNR: ");
        scanf("%14s", danhSachVe[i].maVe);
        while (getchar() != '\n');

        printf("Ho ten hanh khach: ");
        fgets(danhSachVe[i].tenHanhKhach, sizeof(danhSachVe[i].tenHanhKhach), stdin);
        danhSachVe[i].tenHanhKhach[strcspn(danhSachVe[i].tenHanhKhach, "\n")] = '\0'; // Xoa ky tu enter o cuoi chuoi

        printf("Hang ve (Business/Deluxe/Eco): ");
        scanf("%19s", danhSachVe[i].hangVe);
        while (getchar() != '\n');

        // Bat nhap can nang >= 0, nhap sai bat nhap lai
        do {
            printf("Khoi luong hanh ly ky gui (kg): ");
            scanf("%f", &danhSachVe[i].canNangHanhLy);
            while (getchar() != '\n');
            if (danhSachVe[i].canNangHanhLy < 0) {
                printf("Khoi luong hanh ly phai >= 0, vui long nhap lai!\n");
            }
        } while (danhSachVe[i].canNangHanhLy < 0);

        // Tinh cuoc hanh ly: Business mien phi 20kg dau, Eco/Deluxe tinh full
        if (strcmp(danhSachVe[i].hangVe, "Business") == 0) {
            if (danhSachVe[i].canNangHanhLy > 20.0f) {
                danhSachVe[i].cuocHanhLy = (danhSachVe[i].canNangHanhLy - 20.0f) * 50000.0;
            } else {
                danhSachVe[i].cuocHanhLy = 0.0;
            }
        } else {
            danhSachVe[i].cuocHanhLy = danhSachVe[i].canNangHanhLy * 50000.0;
        }
    }

    // 4. Hien thi danh sach ve ban dau dang bang
    printf("\n================================== DANH SACH VE MAY BAY CHUYEN BAY ==================================\n");
    printf("%-5s %-12s %-25s %-12s %12s %15s\n", 
           "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
    printf("----------------------------------------------------------------------------------------------------\n");

    double tongCuoc = 0.0;
    int viTriMax = 0;

    for (int i = 0; i < N; i++) {
        printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
               i + 1,
               danhSachVe[i].maVe,
               danhSachVe[i].tenHanhKhach,
               danhSachVe[i].hangVe,
               danhSachVe[i].canNangHanhLy,
               danhSachVe[i].cuocHanhLy);

        tongCuoc += danhSachVe[i].cuocHanhLy;

        // Tim ve co hanh ly nang nhat
        if (danhSachVe[i].canNangHanhLy > danhSachVe[viTriMax].canNangHanhLy) {
            viTriMax = i;
        }
    }
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Tong tien cuoc hanh ly toan chuyen: %.0f VND\n", tongCuoc);
    printf("Ve co hanh ly ky gui nang nhat: %s - %s (%.1f kg)\n", 
           danhSachVe[viTriMax].maVe, danhSachVe[viTriMax].tenHanhKhach, danhSachVe[viTriMax].canNangHanhLy);

    // 5. Tim kiem va cap nhat hanh ly theo ma PNR
    char pnrCanTim[15];
    printf("\nNhap ma ve PNR can cap nhat hanh ly: ");
    scanf("%14s", pnrCanTim);
    while (getchar() != '\n');

    int indexTimThay = -1;
    for (int i = 0; i < N; i++) {
        if (strcmp(danhSachVe[i].maVe, pnrCanTim) == 0) {
            indexTimThay = i;
            break;
        }
    }

    if (indexTimThay != -1) {
        // Nhap can nang moi hop le
        do {
            printf("Nhap can nang hanh ly ky gui moi (kg): ");
            scanf("%f", &danhSachVe[indexTimThay].canNangHanhLy);
            while (getchar() != '\n');
            if (danhSachVe[indexTimThay].canNangHanhLy < 0) {
                printf("Khoi luong hanh ly phai >= 0, vui long nhap lai!\n");
            }
        } while (danhSachVe[indexTimThay].canNangHanhLy < 0);

        // Tinh lai cuoc sau khi sua
        if (strcmp(danhSachVe[indexTimThay].hangVe, "Business") == 0) {
            if (danhSachVe[indexTimThay].canNangHanhLy > 20.0f) {
                danhSachVe[indexTimThay].cuocHanhLy = (danhSachVe[indexTimThay].canNangHanhLy - 20.0f) * 50000.0;
            } else {
                danhSachVe[indexTimThay].cuocHanhLy = 0.0;
            }
        } else {
            danhSachVe[indexTimThay].cuocHanhLy = danhSachVe[indexTimThay].canNangHanhLy * 50000.0;
        }

        printf("\n--- CAP NHAT THONG TIN HANH LY ---\n");
        printf("Tim thay ma ve %s. Da cap nhat cuoc hanh ly moi: %.0f VND.\n", 
               danhSachVe[indexTimThay].maVe, danhSachVe[indexTimThay].cuocHanhLy);

        // In lai bang sau khi da cap nhat
        printf("\n================================ DANH SACH VE MAY BAY SAU CAP NHAT ================================\n");
        printf("%-5s %-12s %-25s %-12s %12s %15s\n", 
               "STT", "MA VE", "HO TEN HANH KHACH", "HANG VE", "HANH LY (KG)", "CUOC PHI (VND)");
        printf("----------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < N; i++) {
            printf("%-5d %-12s %-25s %-12s %12.1f %15.0f\n",
                   i + 1,
                   danhSachVe[i].maVe,
                   danhSachVe[i].tenHanhKhach,
                   danhSachVe[i].hangVe,
                   danhSachVe[i].canNangHanhLy,
                   danhSachVe[i].cuocHanhLy);
        }
        printf("----------------------------------------------------------------------------------------------------\n");
    } else {
        printf("Khong tim thay ma ve PNR nay trong he thong!\n");
    }

    return 0;
}
