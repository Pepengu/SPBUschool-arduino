template<typename T, uint8_t _size>
class ring_buffer{
private:
    T[size] buffer;
    uint8_t l, r;

    void expand_left();
    void expand_right();

    void shrink_left();
    void shrink_right();

public:
    ring_buffer(): l = 0, r = 0{}

    inline uint8_t size(){
	return (l > r ? l-r : r-l);
    }

    T &operator[](int8_t idx){
	if(idx < 0 || idx > r || l==r){
	    throw;
	}
	return buffer[(idx+l)%_size];
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
	if(size() == 0){
	    throw;
	}

	if(r == 0){
	    return buffer[_size-1];
	}

	return buffer[r-1];
    }


    T& front(){
	if(size() == 0){
	    throw;
	}

	return buffer[(l+1)%_size];
    }

    T& pop_back(){
	T res = back();
	shrink_right();
	return res;
    }

    T& pop_front(){
	T res = front();
	shrink_left();
	return res;
    }
};


template<typename T, uint8_t _size>
void ring_buffer::expand_left(){
    if(this->size() == _size){
	throw;
    }
    if(l == r){
	r = (r + 1) % _size;
    }
    if(l-- == 0){
	l = _size-1;
    }
}

template<typename T, uint8_t _size>
void ring_buffer::expand_right(){
    if(this->size() == _size){
	throw;
    }
    if(l == r){
        if(l-- == 0){
	    l = _size-1;
        }
    }
    r = (r + 1)%_size;
}

template<typename T, uint8_t _size>
void ring_buffer::shrink_left(){
    if(this->size() == 0){
	throw;
    }
    l = (l + 1) % _size;
}

template<typename T, uint8_t _size>
void ring_buffer::shrink_right(){
    if(this->size() == 0){
	throw;
    }
    if(r-- == 0){
	r = _size-1;
    }
}
