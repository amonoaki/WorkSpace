package seqlist;

public class SeqList<T>
{
	//声明数据类型
	protected Object[] element;  //为何要用protected进行保护而不用private, 数组类型为何要是Object而不是T类型
	protected int n;
	//创建并重载构造方法
	public SeqList(int length) {
		this.element = new Object[length];
		this.n = 0;
	}
	public SeqList(T[] values) {
//		this.element = new Object[values.length];  
		this(values.length);  //把给定数组传入顺序表, 没有预留后续空间
		for (int i=0; i < values.length; i++) {  //把数据传入
			this.element[i] = values[i];
		}
		this.n = values.length;
	}
	public SeqList() {  //无参构造方法默认给64个位置
//		this.element = new Object[64];
//		this.n = 0;
		this(64);
	}
	
	//实例方法
	//基本方法
	public boolean isEmpty() {
		return 0 == this.n;
	}
	public int size() {
		return this.n;
	}
	@SuppressWarnings("unchecked")
	public T get(int index) {
		if (index >=0 && index < this.n) {  //检查索引越界
			return (T) this.element[index];
		} else {
			return null;
		}
	}
	public void set(int index, T x) {
		if (null == x) {  //检查数据是否为空
			throw new NullPointerException("x==null");
		}
		if (index >=0 && index < this.n) {  //检查索引越界
			this.element[index] = x;
		} else {
			throw new IndexOutOfBoundsException(index+"OutOfBound");
		}
	}
	public String toString() {  //重写toString
		String str = getClass().getName()+"(";
		if (this.n > 0) {  //先打印第一个元素, 防止逗号多余
			str += this.element[0].toString();
		}
		for (int i=1; i < this.n; i++) {
			str += ","+this.element[i].toString();
		}
		return str+")";
	}
	//数据操作
	//插入数据
	public int insert(int index, T x) {  //插入数据作为第i个元素, 返回插入位置的索引值, 为何要返回索引值?
		if (null == x) {  //检查数据是否为空
			throw new NullPointerException("x==null");
		}
		if (index < 0) {  //防止索引越界
			index = 0;
		}
		if (index > this.n) {
			index = n;
		}
		if (this.n == this.element.length) {  //防止数组溢出
			Object[] oldElement = this.element;
			this.element = new Object[oldElement.length*2];
			for (int i=0; i < oldElement.length; i++) {
				this.element[i] = oldElement[i];
			}
		}
		//插入
		for (int i = this.n; i > index; i--) {
			this.element[i] = this.element[i-1];
		}
		this.element[index] = x;
		this.n++;  //绝对不要忘记了计数器加一
		
		return index;
	}
	public int insert(T x) {  //插入数据未指定序号默认插入到末尾
//		this.insert(this.n, x);
//		return this.n;
		return this.insert(this.n, x);
	}
	//删除数据
	@SuppressWarnings("unchecked")
	public T remove(int index) {  //删除第i个元素, 返回该元素, 为何要返回该元素?
		if (index >=0 && index < this.n) {  //检查索引越界
			T old = (T) this.element[index];  //保存待删除的数据方便返回
			for (int i=index; i < this.n; i++) {
				this.element[i] = this.element[i+1];
			}
			this.element[this.n-1] = null;
			this.n--;  //计数器减一
			
			return old;
		} else {
			throw new IndexOutOfBoundsException(index+"OutOfBound");
		}
	}
	public void clear() {  //清空数据
		this.n = 0;  //只需要把计数器归零即可, 元素实际空间可先不释放, 如果元素数目巨大如何?
	}
	public T remove(T key) {  //按值删除元素
		int index = search(key);
		if (index != -1) {
			return this.remove(index);
		} else {
			return null;
		}
	}
	//查找数据
	public int search(T key) {  //按值查找元素
		for (int i=0; i < this.n; i++) {
			if (key.equals(this.element[i])) {
				return i;
			}
		}
		return -1;
	}
	public boolean contains(T key) {  //判断当前顺序表是否包含该元素
		return (this.search(key) != -1) ? true : false;
	}
	public int insertDifferent(T x) {  //插入不重复的元素, 返回索引位置
		if (null == x) {
			throw new NullPointerException("x==null");
		}
		if (this.search(x) == -1) {
			return this.insert(x);
		} else {
			return -1;
		}
	}
	public boolean equals(Object obj) {  //判断两顺序表所有元素是否对应相等
		if (this.element == obj) {
			return true;
		}
		if (obj instanceof SeqList<?>) {
			SeqList<?> list = (SeqList<?>)obj;
			if (this.n == list.n) {
				for (int i=0; i < this.n; i++) {
					if (!(list.get(i).equals(this.element[i]))) {
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}
	public void addAll(SeqList<? extends T> list) {  //this中添加seqList中所有元素
		for (int i=0; i < list.size(); i++) {
			this.insert(list.get(i));
		}
	}
}
