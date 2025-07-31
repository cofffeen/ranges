#pragma once

template <typename Adapter, typename Functor> 
class FilterIterator {
public:
  using iterator = Adapter::iterator;
  using value_type = Adapter::value_type;
  using iterator_category = std::input_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type;
  using size_type = size_t;

  FilterIterator(const iterator& begin, const iterator& end, Functor func)
      : it_(begin), begin_(begin), end_(end), func_(func) {
    while (it_ != end_ && !func_(*it_)) {
      ++it_;
    }
    begin_ = it_;
  }

  FilterIterator(const FilterIterator &other)
      : it_(other.it_), begin_(other.begin_), end_(other.end_),
        func_(other.func_) {}

  ~FilterIterator() = default;

  FilterIterator &operator=(const FilterIterator &other) {
    it_ = other.it_;
    begin_ = other.begin_;
    end_ = other.end_;
    func_ = other.func_;

    return *this;
  }

  reference operator*() const { return *it_; }

  bool operator==(const FilterIterator &other) const {
    return (it_ == other.it_);
  }

  bool operator!=(const FilterIterator &other) const {
    return !(*this == other);
  }

  FilterIterator &operator++() {
    do {
      ++it_;
    } while (it_ != end_ && !func_(*it_));
    return *this;
  }

  FilterIterator operator++(int) {
    FilterIterator<Adapter, Functor> copy = *this;
    ++(*this);
    return copy;
  }

private:
  iterator it_;
  iterator begin_;
  iterator end_;
  Functor func_;
};