#define NULL_PTR (void *)0

#define TRUE 1
#define FALSE 0

typedef unsigned char Std_ReturnType;

typedef struct List_STag
{
  struct List_STag *_pre;
  void *data_ptr;
  struct List_STag *_next;
} List;

unsigned char arr[4] = {1, 2, 3, 4};
List mylist =
{
  NULL_PTR,
  arr,
  NULL_PTR
};
Std_ReturnType add_list(List* ele);

int main(void)
{
  List newEle;
  int LucVar[2] = {2,2};
  newEle.data_ptr = LucVar;
  add_list(&newEle);
  arr[0] = 0xFF;
  while(1)
  {
    
  }
  return 0;
}

Std_ReturnType add_list(List* ele)
{
  mylist._next = ele;
  ele->_pre = &mylist;
}

void System_Init(void)
{
  arr[0] = 0xFF;
}