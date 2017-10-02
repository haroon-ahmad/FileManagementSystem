template <typename T>
class stack
{
private:
	T *sptr;
	int top;
	int size;
	void increase(int &size);
public:
	stack();
	stack(int size);
	bool isfull();
	bool isempty();
	int getsize();
	int gettop();
	void push(const T&);
	bool pop(T&);
};
template <typename T>
stack<T>::stack()
{
	size=5;
	top=-1;
	sptr=new T [5];
}
template <typename T>
stack<T>::stack(int _size=0)
{
	size=_size;
	top=-1;
	sptr=new T[size];
}
template <typename T>
int stack<T>::getsize()
{
	return size;
}
template <typename T>
void stack<T>::increase(int &size)
{
	T* temp;
	temp=new T[size*2];
	for(int i=0;i<size;i++)
	{
		temp[i]=sptr[i];
	}
	delete []sptr;
	size=size*2;
	sptr=temp;
}
template <typename T>
bool stack <T>::isfull()
{
	return (top==(size-1));
}
template <typename T>
bool stack<T>::isempty()
{
	return (top==-1);
}
template <typename T>
void stack<T>::push(const T& element)
{
	if(isfull())
	{
		increase(size);
	}
	sptr[++top]=element;
}
template <typename T>
bool stack<T>::pop(T &element)
{
	if(isempty()==true)
	{
		return false;
	}
		element=sptr[top--];
		return true;
}
template<typename T>
int stack<T>::gettop()
{
	return top;
}
