#include <vector>
#include <time.h>
#include <iostream>
#include <time.h>
#include <fstream>  


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

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(std::vector<int> &array, int front, int end){
    int pivot = array[end];
    int i = front -1;
    for (int j = front; j < end; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    i++;
    swap(&array[i], &array[end]);
    return i;
}
void QuickSort(std::vector<int> &array, int front, int end){
    if (front < end) {
        int pivot = Partition(array, front, end);
        QuickSort(array, front, pivot - 1);
        QuickSort(array, pivot + 1, end);
    }
}
void Printarrayay(int *array, int size){
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
	
	time_t c_start, t_start, c_end, t_end;
	

    std::vector<int> vecOfStr;
    // Get the contents of file in a vector
    bool result = getFileContent("radom.txt", vecOfStr);
    int array[vecOfStr.size()];
 
    if(result)
    {
    
        // Print the vector contents
   		std::copy(vecOfStr.begin(), vecOfStr.end(), array);
	}
    
 
	c_start = clock(); //s 
	
	
	t_start = time(NULL);  //ms


int checkEnd =vecOfStr.size()-1;
    QuickSort(vecOfStr, 0, checkEnd);

   	c_end   = clock();
	t_end	= time(NULL);

	printf("The pause used %f ms by clock()\n",difftime(c_end,c_start)); 
	printf("The pause used %f s by time()\n",difftime(t_end,t_start));

//	for(int i=0 ;i <vecOfStr.size();i++){
//		       std::cout << vecOfStr.at(i);
//	          std::cout << "\n";
//	}
    return 0;
}
