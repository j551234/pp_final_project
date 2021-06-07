// C++ code
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>  
#include <omp.h>
const int Max = 10000000;
using namespace std;

bool getFileContent(std::string fileName, std::vector<int> & vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(stoi(str));
    }
    //Close The File
    in.close();
    return true;
}

void Merge(std::vector<int> &Array, int front, int mid, int end){

    // 利用 std::vector 的constructor, 
    // 把array[front]~array[mid]放進 LeftSub[]
    // 把array[mid+1]~array[end]放進 RightSub[]
    std::vector<int> LeftSub(Array.begin()+front, Array.begin()+mid+1),
                     RightSub(Array.begin()+mid+1, Array.begin()+end+1);

    LeftSub.insert(LeftSub.end(), Max);      // 在LeftSub[]尾端加入值為 Max 的元素
    RightSub.insert(RightSub.end(), Max);    // 在RightSub[]尾端加入值為 Max 的元素

    int idxLeft = 0, idxRight = 0;

    for (int i = front; i <= end; i++) {

        if (LeftSub[idxLeft] <= RightSub[idxRight] ) {
            Array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else{
            Array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
}

void MergeSort(std::vector<int> &array, int front, int end){
                                         // front與end為矩陣範圍
    if (front < end) {                   // 表示目前的矩陣範圍是有效的
        int mid = (front+end)/2;         // mid即是將矩陣對半分的index
        #pragma omp task firstprivate (array, front, mid)
        MergeSort(array, front, mid);    // 繼續divide矩陣的前半段subarray
        #pragma omp task firstprivate (array, front, mid)
        MergeSort(array, mid+1, end);
        #pragma omp taskwait    // 繼續divide矩陣的後半段subarray
        Merge(array, front, mid, end);   // 將兩個subarray做比較, 並合併出排序後的矩陣
    }
}



int main() {
	
	double start, stop;
	// time_t c_start, t_start, c_end, t_end;
	


    std::vector<int> vecOfStr;
    // Get the contents of file in a vector
    bool result = getFileContent("radom.txt", vecOfStr);
    int arr[vecOfStr.size()];
 
    if(result)
    {
    
        // Print the vector contents
   		std::copy(vecOfStr.begin(), vecOfStr.end(), arr);
	}
    
 
	// c_start = clock(); //s 
	
	
	// t_start = time(NULL);  //ms
    omp_set_num_threads(4);//調整thread數量
start = omp_get_wtime();
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Thread is %d\n",id);
    #pragma omp single
    MergeSort(vecOfStr, 0, vecOfStr.size());
    }
   	// c_end   = clock();
	// t_end	= time(NULL);
stop = omp_get_wtime();
	// printf("The pause used %f ms by clock()\n",difftime(c_end,c_start)); 
	// printf("The pause used %f s by time()\n",difftime(t_end,t_start));
    printf("\nTime: %g\n",stop-start);

//	for(int i=0 ;i <vecOfStr.size();i++){
//		       cout << vecOfStr.at(i);
//	         cout << "\n";
//	}


    return 0;
}