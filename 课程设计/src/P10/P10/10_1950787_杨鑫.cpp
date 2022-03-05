# include <iostream>
#include <stdlib.h>
# include <limits>
#include <time.h> 

using namespace std;

# define MAXNUMS 10000 // 最大数字个数
# define RANDOM_LENGTH 7 // 随机数的位数
int tem[MAXNUMS + 5]; // 额外临时数组

// 系统类，整合了所有排序算法
class System {
private :
	int nums; // 随机数个数
	long long exchangeNums; // 交换次数
	long long compareNums; // 比较次数
	int array[MAXNUMS + 5]; // 数组
	void swap(int i, int j); // 交换
	void quickSort(int left, int right); // 快速排序
	void mergeSort(int left, int right); // 归并排序
	void siftDown(int start, int end); // 堆的下移函数
	void radixSort(int left, int right, int rank); // 基数排序
	int getRank(int num, int rank); // 得到一个数字的某一位
public :
	System() : nums(0), exchangeNums(0), compareNums(0) {} // 构造函数
	void loop(); // 主循环

	void getRand(int nums); // 产生随机数
	void bubbleSort(); // 冒泡排序
	void selectionSort(); // 选择排序
	void insertSort(); // 插入排序
	void shellSort(); // 希尔排序
	void quickSort(); // 快速排序
	void heapSort(); // 堆排序
	void mergeSort(); // 归并排序
	void radixSort(); // 基数排序
};

// 产生随机数
void System::getRand(int num) {
	this->nums = num;
	srand((unsigned)time(NULL));

	// 产生 num 个随机数
	for (int i = 0; i < num; i++) {
		array[i] = 0;

		// 对每一个随机数，产生 RANDOM_LENGTH 个 0~9 的数字，分别作为其最高位至最低位的数字
		for (int j = 0; j < RANDOM_LENGTH; j++) {
			array[i] = rand() % 10 + array[i] * 10;
		}
	}
}

// 交换函数
void System::swap(int i, int j) {
	// 交换次数 + 1
	exchangeNums++;
	int tem = array[i];
	array[i] = array[j];
	array[j] = tem;
}

// 冒泡排序
void System::bubbleSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	for (int i = 0; i < nums - 1; i++) {
		bool tag = false; // 记录本次循环是否交换
		for (int j = 0; j < nums - 1 - i; j++) {
			compareNums++;
			if (array[j] > array[j + 1]) {
				swap(j, j + 1);
				tag = true;
			}
		}

		// 如果某次循环没有交换了，说明剩下的已经全部有序，不需要再排序
		if (!tag) {
			return;
		}
	}
}

// 选择排序
void System::selectionSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	// 初始化
	int left = 0, right = nums - 1;
	int min = left, max = right;

	while (left < right) {
		// 分别将最左边的记录为 min，最右边的记录为 max
		min = left, max = right;

		// 在遍历的时候更新 min，max
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

		// 从头和尾分别遍历，可以使循环次数减半
		left++, right--;
	}
}

// 直接插入排序
void System::insertSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	// 从第 1 个数字开始不断按顺序插入
	for (int i = 1; i < nums; i++) {
		int insertedNum = array[i];
		int j = i - 1;

		// 寻找插入位置
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

// 希尔排序
void System::shellSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	// 初始化 gap
	int gap = nums;

	// 不断循环，直至 gap 为 1
	do {
		gap = gap / 3 + 1;

		// 以间隔为 gap 进行直接插入排序
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

// 快速排序（递归）
void System::quickSort(int left, int right) {
	// 递归终止条件
	if (left >= right) return;

	int i = left - 1, j = right + 1, tem = array[left + right >> 1];

	// 不断从两边交换元素，直至两边相遇
	while (i < j) {
		do i++, compareNums++; while (array[i] < tem);
		do j--, compareNums++; while (array[j] > tem);

		if (i < j) swap(i, j);
	}

	// 递归对两个子序列排序
	quickSort(left, j);
	quickSort(j + 1, right);
}

// 快速排序
void System::quickSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	// 对所有元素进行快速排序
	quickSort(0, nums - 1);
}

// 堆的下移函数
void System::siftDown(int start, int end) {
	// 记录当前位置及当前位置左子女
	int current = start, maxChild = 2 * start + 1;
	int tem = array[current];

	// 下移调整至最后一个元素
	while (maxChild <= end) {
		compareNums++;
		// 选择当前元素中最大的一个子女
		if (maxChild < end && array[maxChild] < array[maxChild + 1]) maxChild++, compareNums++;
		// 当前元素已经符合最大堆的要求
		if (tem > array[maxChild]) {
			compareNums++; 
			break;
		}
		// 否则，大的上移，小的小调
		else {
			swap(current, maxChild);
			current = maxChild;
			maxChild = maxChild * 2 + 1;
		}
	}
	array[current] = tem;
}

// 堆排序
void System::heapSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	// 自底向上建立最大堆
	for (int i = (nums - 2) / 2; i >= 0; i--) {
		siftDown(i, nums - 1);
	}

	// 逐个从堆顶取出最大元素放在最后
	for (int i = nums - 1; i > 0; i--) {
		swap(0, i);
		siftDown(0, i - 1);
	}
}

// 归并排序（递归）
void System::mergeSort(int left, int right) {
	// 终止条件
	if (left >= right) return;

	// 递归对两个子序列排序
	int mid = (left + right) / 2;
	mergeSort(left, mid);
	mergeSort(mid + 1, right);

	// 合并区间
	int p = left, q = mid + 1, k = 0;
	while (p <= mid && q <= right) {
		exchangeNums++;
		compareNums ++;
		if (array[p] < array[q]) tem[k++] = array[p++];
		else tem[k++] = array[q++];
	}

	// 对还没合并完的子序列进行插入
	while (p <= mid) {
		exchangeNums++;
		tem[k++] = array[p++];
	}
	while (q <= right) { 
		exchangeNums++;
		tem[k++] = array[q++]; 
	}

	// 从临时数组复制到真实的数组中
	for (int i = left, j = 0; i <= right; i++, j++) {
		array[i] = tem[j];
	}
}

// 归并排序
void System::mergeSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;

	// 对所有元素排序
	mergeSort(0, nums - 1);
}

// 得到一个数的某一位的数字
int System::getRank(int num, int rank) {
	// 取出第 rank 位
	for (int i = 1; i < rank; i++) {
		num /= 10;
	}
	return num % 10;
}

// MSD 基数排序（递归）
void System::radixSort(int left, int right, int rank) {
	// radix 设定为 10
	int radix = 10;
	if (rank < 1) return;
	if (left >= right) return;

	// 临时数组
	int* count = new int[radix + 1];
	int* buket = new int[right - left + 1];

	// 初始化
	for (int i = 0; i < radix; i++) {
		count[i] = 0;
	}
	// 统计每个 buket 中的数字
	for (int i = left; i <= right; i++) {
		count[getRank(array[i], rank)]++;
	}
	// 根据统计的数字确定每一组的末尾元素的位置
	for (int i = 1; i < radix; i++) {
		count[i] += count[i - 1];
	}
	count[radix] = count[radix - 1] + 1; // 人为的将最后多的一个 count 数组的元素赋值为上一个元素 + 1
	for (int i = left; i <= right; i++) {
		// 得到第 rank 位的排序码
		int tem = getRank(array[i], rank);
		// 将元素放入桶中
		buket[count[tem] - 1] = array[i];
		exchangeNums++;
		count[tem]--;
	}
	// 将元素从桶中复制回原数组
	for (int i = left, j = 0; i <= right; i++, j++) {
		exchangeNums++;
		array[i] = buket[j];
	}

	// 递归排序下一位
	for (int i = 0; i < radix; i++) {
		int nextLeft = count[i];
		int nextRight = count[i + 1] - 1;
		radixSort(nextLeft, nextRight, rank - 1);
	}
	// 删除临时数组
	delete[] count;
	delete[] buket;
}

// 基数排序
void System::radixSort() {
	// 置交换次数和比较次数为 0
	exchangeNums = 0;
	compareNums = 0;
	
	// 对所有数字排序，置最高位为首次排序关键码
	radixSort(0, nums - 1, RANDOM_LENGTH);
}

// 主循环
void System::loop() {
	cout << "**                   排序算法比较                   **" << endl;
	cout << "======================================================" << endl;
	cout << "**               请选择要执行的操作：               **" << endl;
	cout << "**               1 --- 冒泡排序                     **" << endl;
	cout << "**               2 --- 选择排序                     **" << endl;
	cout << "**               3 --- 直接插入排序                 **" << endl;
	cout << "**               4 --- 希尔排序                     **" << endl;
	cout << "**               5 --- 快速排序                     **" << endl;
	cout << "**               6 --- 堆排序                       **" << endl;
	cout << "**               7 --- 归并排序                     **" << endl;
	cout << "**               8 --- 基数排序                     **" << endl;
	cout << "**               9 --- 退出程序                     **" << endl;
	cout << "======================================================" << endl << endl;

	cout << "请输入要产生的随机数的个数：";
	int nums;
	cin >> nums;

	// 检验数字合法性
	while (nums < 1 || nums > MAXNUMS) {
		cout << "个数必须大于0且小于10000，请重新输入：" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> nums;
	}

	// 不断接受指令并执行
	while (true) {
		cout << "请选择排序算法：";
		int op;
		cin >> op;
		clock_t start, end;
		string str;
		
		getRand(nums); // 产生随机数
		start = clock(); // 记录起始时间点
		switch (op) {
		case 1:
			// 冒泡排序
			bubbleSort();
			str = "冒泡排序";
			break;
		case 2:
			// 选择排序
			selectionSort();
			str = "选择排序";
			break;
		case 3:
			// 直接插入排序
			insertSort();
			str = "直接插入排序";
			break;
		case 4:
			// 希尔排序
			shellSort();
			str = "希尔排序";
			break;
		case 5:
			// 快速排序
			quickSort();
			str = "快速排序";
			break;
		case 6:
			// 堆排序
			heapSort();
			str = "堆排序";
			break;
		case 7:
			// 归并排序
			mergeSort();
			str = "归并排序";
			break;
		case 8:
			// 基数排序
			radixSort();
			str = "基数排序";
			break;
		case 9:
			// 退出程序
			cout << "本次操作完成，欢迎下次光临！" << endl << endl;
			return;
			break;
		default:
			// 非法输入
			cout << "非法操作符，请重新输入：";
			// 清空缓冲区
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		// 记录结束时间点
		end = clock();
		cout << str << "所用时间：    " << ((double)(end - start) / CLOCKS_PER_SEC) * 1000 << "  毫秒" << endl;
		cout << str << "所用交换次数：    " << exchangeNums << "  次" << endl;
		if (op != 8) {
			cout << str << "所用比较次数：    " << compareNums << "  次" << endl << endl;
		}
		else {
			cout << str << "不需要进行关键码的比较" << endl << endl;
		}
	}
}


int main() {
	// 实例化系统并进入主循环
	System sys;
	sys.loop();

	// windows 系统暂停一下防止闪退，LINUX则不用
# ifdef _WIN32
	system("pause");
# endif

	return 0;
}