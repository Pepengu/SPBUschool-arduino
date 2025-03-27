template<typename T, uint8_t _size>
class ring_buffer{
	private:
		T buffer[_size];
		uint8_t l, r;

		void expand_left();
		void expand_right();

		void shrink_left();
		void shrink_right();

	public:
		ring_buffer(): l(0), r(0){}

		inline uint8_t size(){
			return (r-l+_size-1)%_size;
		}

		T &operator[](int8_t idx){
			return buffer[(idx+l+1)%_size];
		}

		void push_back(const T& val){
			buffer[r] = val; 
			expand_right();
		}

		void push_front(const T& val){
			buffer[l] = val; 
			expand_left();
		}

		T& back(){
			if(r == 0){
				return buffer[_size-1];
			}

			return buffer[r-1];
		}


		T& front(){
			return buffer[(l+1)%_size];
		}

		T pop_back(){
			T res = back();
			shrink_right();
			return res;
		}

		T pop_front(){
			T res = front();
			shrink_left();
			return res;
		}
};


template<typename T, uint8_t _size>
void ring_buffer<T,_size>::expand_left(){
	if(l == r){
		r = (r + 1) % _size;
	}
	if(l-- == 0){
		l = _size-1;
	}
}

template<typename T, uint8_t _size>
void ring_buffer<T,_size>::expand_right(){
	if(l == r){
		if(l-- == 0){
			l = _size-1;
		}
	}
	r = (r + 1)%_size;
}

template<typename T, uint8_t _size>
void ring_buffer<T,_size>::shrink_left(){
	l = (l + 1) % _size;
}

template<typename T, uint8_t _size>
void ring_buffer<T,_size>::shrink_right(){
	if(r-- == 0){
		r = _size-1;
	}
}
