
#include <iostream>

using namespace std;


class MergeSort {
private:
	int temp[10];
public:
	void merge(int*, int, int, int);
	void merge_sort(int*, int, int);
};

void MergeSort::merge(int* arr, int left, int middle, int right) {
	
	int i, j, k;

	i = left;
	j = middle + 1;
	k = left; // 임시 배열 인덱스 값

	while ( i <= middle && j <= right ) {

		if (arr[i] <= arr[j]) {
			temp[k] = arr[i++];
		}
		else {
			temp[k] = arr[j++];
		}
		k++;
	}

	if (i > middle) { // 나머지 삽입
		for (int tmp = j; tmp <= right; tmp++) {
			temp[k++] = arr[tmp];
		}
	}
	else {
		for (int tmp = i; tmp <= middle; tmp++) {
			temp[k++] = arr[tmp];
		}
	}

	for (int tmp = left; tmp <= right; tmp++) { // 기존 배열에 삽입
		arr[tmp] = temp[tmp];
	}

}

void MergeSort::merge_sort(int* arr, int left, int right) {

	int mid;

	if (left < right) {

		mid = (left + right) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}

}



int main() {

	MergeSort ms;

	int arr[] = { 10, 4, 2, 7, 9, 3, 5, 1, 8, 6 };
	
	cout << "============================================" << endl;

	for (int i = 0; i < 10; i++) {
		if (i > 0 && i < 9) {
			cout << arr[i] << ", ";
		}
		else if (i == 0) {
			cout << "정렬 전 :: [ " << arr[i] << ", ";
		}
		else {
			cout << arr[i] << " ]" << endl;
		}
	}

	cout << "============================================" << endl;
	cout << "================ Merge Sort ================" << endl;
	cout << "============================================" << endl;

	ms.merge_sort(arr, 0, 9);

	for (int i = 0; i < 10; i++) {
		if (i > 0 && i < 9) {
			cout << arr[i] << ", ";
		}
		else if (i == 0) {
			cout << "정렬 후 :: [ " << arr[i] << ", ";
		}
		else {
			cout << arr[i] << " ]" << endl;
		}
	}
	cout << "============================================" << endl;

	return 0;
}