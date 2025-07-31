#pragma once

template <typename Adapter, typename Functor> 
class TransformIterator {
public:
  using iterator = decltype(std::declval<const Adapter &>().begin());
  using value_type =
      decltype(std::declval<Functor>()(*std::declval<iterator>()));
  using iterator_category = std::input_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using reference = value_type;
  using size_type = size_t;

  TransformIterator(const iterator &begin, const iterator &end,
                    const Functor &func)
      : it_(begin), begin_(begin), end_(end), func_(func) {}

  TransformIterator(const TransformIterator &other)
      : it_(other.it_), begin_(other.begin_), end_(other.end_),
        func_(other.func_) {}

  ~TransformIterator() = default;

  TransformIterator &operator=(const TransformIterator &other) {
    it_ = other.it_;
    begin_ = other.begin_;
    end_ = other.end_;
    func_ = other.func_;

    return *this;
  }

  reference operator*() const { return func_(*it_); }

  bool operator==(const TransformIterator &other) const {
    return (it_ == other.it_);
  }

  bool operator!=(const TransformIterator &other) const {
    return !(*this == other);
  }

  TransformIterator &operator++() {
    ++it_;
    return *this;
  }

  TransformIterator operator++(int) {
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