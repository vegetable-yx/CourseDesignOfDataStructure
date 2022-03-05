# include <iostream>
#include <stdlib.h>
# include <limits>
#include <time.h> 

using namespace std;

# define MAXNUMS 10000 // ������ָ���
# define RANDOM_LENGTH 7 // �������λ��
int tem[MAXNUMS + 5]; // ������ʱ����

// ϵͳ�࣬���������������㷨
class System {
private :
	int nums; // ���������
	long long exchangeNums; // ��������
	long long compareNums; // �Ƚϴ���
	int array[MAXNUMS + 5]; // ����
	void swap(int i, int j); // ����
	void quickSort(int left, int right); // ��������
	void mergeSort(int left, int right); // �鲢����
	void siftDown(int start, int end); // �ѵ����ƺ���
	void radixSort(int left, int right, int rank); // ��������
	int getRank(int num, int rank); // �õ�һ�����ֵ�ĳһλ
public :
	System() : nums(0), exchangeNums(0), compareNums(0) {} // ���캯��
	void loop(); // ��ѭ��

	void getRand(int nums); // ���������
	void bubbleSort(); // ð������
	void selectionSort(); // ѡ������
	void insertSort(); // ��������
	void shellSort(); // ϣ������
	void quickSort(); // ��������
	void heapSort(); // ������
	void mergeSort(); // �鲢����
	void radixSort(); // ��������
};

// ���������
void System::getRand(int num) {
	this->nums = num;
	srand((unsigned)time(NULL));

	// ���� num �������
	for (int i = 0; i < num; i++) {
		array[i] = 0;

		// ��ÿһ������������� RANDOM_LENGTH �� 0~9 �����֣��ֱ���Ϊ�����λ�����λ������
		for (int j = 0; j < RANDOM_LENGTH; j++) {
			array[i] = rand() % 10 + array[i] * 10;
		}
	}
}

// ��������
void System::swap(int i, int j) {
	// �������� + 1
	exchangeNums++;
	int tem = array[i];
	array[i] = array[j];
	array[j] = tem;
}

// ð������
void System::bubbleSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	for (int i = 0; i < nums - 1; i++) {
		bool tag = false; // ��¼����ѭ���Ƿ񽻻�
		for (int j = 0; j < nums - 1 - i; j++) {
			compareNums++;
			if (array[j] > array[j + 1]) {
				swap(j, j + 1);
				tag = true;
			}
		}

		// ���ĳ��ѭ��û�н����ˣ�˵��ʣ�µ��Ѿ�ȫ�����򣬲���Ҫ������
		if (!tag) {
			return;
		}
	}
}

// ѡ������
void System::selectionSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	// ��ʼ��
	int left = 0, right = nums - 1;
	int min = left, max = right;

	while (left < right) {
		// �ֱ�����ߵļ�¼Ϊ min�����ұߵļ�¼Ϊ max
		min = left, max = right;

		// �ڱ�����ʱ����� min��max
		for (int i = left; i < right; i++) {
			compareNums += 2;
			if (array[i] < array[min]) {
				min = i;
			}
			if (array[i] > array[max]) {
				max = i;
			}
		}

		if (min != left) {
			swap(min, left);
		}
		if (max != right) {
			swap(max, right);
		}

		// ��ͷ��β�ֱ����������ʹѭ����������
		left++, right--;
	}
}

// ֱ�Ӳ�������
void System::insertSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	// �ӵ� 1 �����ֿ�ʼ���ϰ�˳�����
	for (int i = 1; i < nums; i++) {
		int insertedNum = array[i];
		int j = i - 1;

		// Ѱ�Ҳ���λ��
		while (j >= 0 && array[j] > insertedNum) {
			compareNums++;
			array[j + 1] = array[j];
			exchangeNums++;
			j--;
		}
		compareNums++;
		array[j + 1] = insertedNum;
	}
}

// ϣ������
void System::shellSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	// ��ʼ�� gap
	int gap = nums;

	// ����ѭ����ֱ�� gap Ϊ 1
	do {
		gap = gap / 3 + 1;

		// �Լ��Ϊ gap ����ֱ�Ӳ�������
		for (int i =0 + gap; i < nums; i++) {
			compareNums++;
			if (array[i] < array[i - gap]) {
				int insertNum = array[i];
				int j = i - gap;
				while (j >= 0 && array[j] > insertNum) {
					array[j + gap] = array[j];
					compareNums++;
					exchangeNums++;
					j -= gap;
				}
				compareNums++;
				array[j + gap] = insertNum;
			}
		}
	} while (gap > 1);
}

// �������򣨵ݹ飩
void System::quickSort(int left, int right) {
	// �ݹ���ֹ����
	if (left >= right) return;

	int i = left - 1, j = right + 1, tem = array[left + right >> 1];

	// ���ϴ����߽���Ԫ�أ�ֱ����������
	while (i < j) {
		do i++, compareNums++; while (array[i] < tem);
		do j--, compareNums++; while (array[j] > tem);

		if (i < j) swap(i, j);
	}

	// �ݹ����������������
	quickSort(left, j);
	quickSort(j + 1, right);
}

// ��������
void System::quickSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	// ������Ԫ�ؽ��п�������
	quickSort(0, nums - 1);
}

// �ѵ����ƺ���
void System::siftDown(int start, int end) {
	// ��¼��ǰλ�ü���ǰλ������Ů
	int current = start, maxChild = 2 * start + 1;
	int tem = array[current];

	// ���Ƶ��������һ��Ԫ��
	while (maxChild <= end) {
		compareNums++;
		// ѡ��ǰԪ��������һ����Ů
		if (maxChild < end && array[maxChild] < array[maxChild + 1]) maxChild++, compareNums++;
		// ��ǰԪ���Ѿ��������ѵ�Ҫ��
		if (tem > array[maxChild]) {
			compareNums++; 
			break;
		}
		// ���򣬴�����ƣ�С��С��
		else {
			swap(current, maxChild);
			current = maxChild;
			maxChild = maxChild * 2 + 1;
		}
	}
	array[current] = tem;
}

// ������
void System::heapSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	// �Ե����Ͻ�������
	for (int i = (nums - 2) / 2; i >= 0; i--) {
		siftDown(i, nums - 1);
	}

	// ����ӶѶ�ȡ�����Ԫ�ط������
	for (int i = nums - 1; i > 0; i--) {
		swap(0, i);
		siftDown(0, i - 1);
	}
}

// �鲢���򣨵ݹ飩
void System::mergeSort(int left, int right) {
	// ��ֹ����
	if (left >= right) return;

	// �ݹ����������������
	int mid = (left + right) / 2;
	mergeSort(left, mid);
	mergeSort(mid + 1, right);

	// �ϲ�����
	int p = left, q = mid + 1, k = 0;
	while (p <= mid && q <= right) {
		exchangeNums++;
		compareNums ++;
		if (array[p] < array[q]) tem[k++] = array[p++];
		else tem[k++] = array[q++];
	}

	// �Ի�û�ϲ���������н��в���
	while (p <= mid) {
		exchangeNums++;
		tem[k++] = array[p++];
	}
	while (q <= right) { 
		exchangeNums++;
		tem[k++] = array[q++]; 
	}

	// ����ʱ���鸴�Ƶ���ʵ��������
	for (int i = left, j = 0; i <= right; i++, j++) {
		array[i] = tem[j];
	}
}

// �鲢����
void System::mergeSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;

	// ������Ԫ������
	mergeSort(0, nums - 1);
}

// �õ�һ������ĳһλ������
int System::getRank(int num, int rank) {
	// ȡ���� rank λ
	for (int i = 1; i < rank; i++) {
		num /= 10;
	}
	return num % 10;
}

// MSD �������򣨵ݹ飩
void System::radixSort(int left, int right, int rank) {
	// radix �趨Ϊ 10
	int radix = 10;
	if (rank < 1) return;
	if (left >= right) return;

	// ��ʱ����
	int* count = new int[radix + 1];
	int* buket = new int[right - left + 1];

	// ��ʼ��
	for (int i = 0; i < radix; i++) {
		count[i] = 0;
	}
	// ͳ��ÿ�� buket �е�����
	for (int i = left; i <= right; i++) {
		count[getRank(array[i], rank)]++;
	}
	// ����ͳ�Ƶ�����ȷ��ÿһ���ĩβԪ�ص�λ��
	for (int i = 1; i < radix; i++) {
		count[i] += count[i - 1];
	}
	count[radix] = count[radix - 1] + 1; // ��Ϊ�Ľ������һ�� count �����Ԫ�ظ�ֵΪ��һ��Ԫ�� + 1
	for (int i = left; i <= right; i++) {
		// �õ��� rank λ��������
		int tem = getRank(array[i], rank);
		// ��Ԫ�ط���Ͱ��
		buket[count[tem] - 1] = array[i];
		exchangeNums++;
		count[tem]--;
	}
	// ��Ԫ�ش�Ͱ�и��ƻ�ԭ����
	for (int i = left, j = 0; i <= right; i++, j++) {
		exchangeNums++;
		array[i] = buket[j];
	}

	// �ݹ�������һλ
	for (int i = 0; i < radix; i++) {
		int nextLeft = count[i];
		int nextRight = count[i + 1] - 1;
		radixSort(nextLeft, nextRight, rank - 1);
	}
	// ɾ����ʱ����
	delete[] count;
	delete[] buket;
}

// ��������
void System::radixSort() {
	// �ý��������ͱȽϴ���Ϊ 0
	exchangeNums = 0;
	compareNums = 0;
	
	// �������������������λΪ�״�����ؼ���
	radixSort(0, nums - 1, RANDOM_LENGTH);
}

// ��ѭ��
void System::loop() {
	cout << "**                   �����㷨�Ƚ�                   **" << endl;
	cout << "======================================================" << endl;
	cout << "**               ��ѡ��Ҫִ�еĲ�����               **" << endl;
	cout << "**               1 --- ð������                     **" << endl;
	cout << "**               2 --- ѡ������                     **" << endl;
	cout << "**               3 --- ֱ�Ӳ�������                 **" << endl;
	cout << "**               4 --- ϣ������                     **" << endl;
	cout << "**               5 --- ��������                     **" << endl;
	cout << "**               6 --- ������                       **" << endl;
	cout << "**               7 --- �鲢����                     **" << endl;
	cout << "**               8 --- ��������                     **" << endl;
	cout << "**               9 --- �˳�����                     **" << endl;
	cout << "======================================================" << endl << endl;

	cout << "������Ҫ������������ĸ�����";
	int nums;
	cin >> nums;

	// �������ֺϷ���
	while (nums < 1 || nums > MAXNUMS) {
		cout << "�����������0��С��10000�����������룺" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> nums;
	}

	// ���Ͻ���ָ�ִ��
	while (true) {
		cout << "��ѡ�������㷨��";
		int op;
		cin >> op;
		clock_t start, end;
		string str;
		
		getRand(nums); // ���������
		start = clock(); // ��¼��ʼʱ���
		switch (op) {
		case 1:
			// ð������
			bubbleSort();
			str = "ð������";
			break;
		case 2:
			// ѡ������
			selectionSort();
			str = "ѡ������";
			break;
		case 3:
			// ֱ�Ӳ�������
			insertSort();
			str = "ֱ�Ӳ�������";
			break;
		case 4:
			// ϣ������
			shellSort();
			str = "ϣ������";
			break;
		case 5:
			// ��������
			quickSort();
			str = "��������";
			break;
		case 6:
			// ������
			heapSort();
			str = "������";
			break;
		case 7:
			// �鲢����
			mergeSort();
			str = "�鲢����";
			break;
		case 8:
			// ��������
			radixSort();
			str = "��������";
			break;
		case 9:
			// �˳�����
			cout << "���β�����ɣ���ӭ�´ι��٣�" << endl << endl;
			return;
			break;
		default:
			// �Ƿ�����
			cout << "�Ƿ������������������룺";
			// ��ջ�����
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		// ��¼����ʱ���
		end = clock();
		cout << str << "����ʱ�䣺    " << ((double)(end - start) / CLOCKS_PER_SEC) * 1000 << "  ����" << endl;
		cout << str << "���ý���������    " << exchangeNums << "  ��" << endl;
		if (op != 8) {
			cout << str << "���ñȽϴ�����    " << compareNums << "  ��" << endl << endl;
		}
		else {
			cout << str << "����Ҫ���йؼ���ıȽ�" << endl << endl;
		}
	}
}


int main() {
	// ʵ����ϵͳ��������ѭ��
	System sys;
	sys.loop();

	// windows ϵͳ��ͣһ�·�ֹ���ˣ�LINUX����
# ifdef _WIN32
	system("pause");
# endif

	return 0;
}