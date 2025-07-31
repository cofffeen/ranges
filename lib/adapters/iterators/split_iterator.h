#pragma once

template <typename Adapter> 
class SplitIterator {
public:
  using iterator = Adapter::iterator;
  using difference_type = std::ptrdiff_t;
  using value_type = std::string;
  using reference = std::string;
  using iterator_category = std::input_iterator_tag;

  SplitIterator(const iterator &begin, const iterator &end, const std::string &delimeter)
      : it_(begin), end_(end), delimeter_(delimeter) {
    if (it_ != end_) {
      SetSubstr();
    }
  }

  SplitIterator(const SplitIterator &other)
      : it_(other.it_), end_(other.end_), delimeter_(other.delimeter_),
        substr_(other.substr_) {}

  ~SplitIterator() = default;

  SplitIterator &operator=(const SplitIterator &other) {
    it_ = other.it_;
    end_ = other.end_;
    delimeter_ = other.delimeter_;
    substr_ = other.substr_;

    return *this;
  }

  reference operator*() const { return substr_; }

  bool operator==(const SplitIterator &other) const {
    return (it_ == other.it_);
  }

  bool operator!=(const SplitIterator &other) const {
    return !(*this == other);
  }

  SplitIterator &operator++() {
    if (!(*it_)) {
      ++it_;
    }

    if (it_ != end_) {
      SetSubstr();
    }

    return *this;
  }

  SplitIterator operator++(int) {
    SplitIterator<Adapter> copy = *this;
    ++(*this);
    return copy;
  }

private:
  iterator it_;
  iterator end_;
  const std::string& delimeter_;

  std::string substr_;

  void SetSubstr() {
    substr_ = "";
    char symbol;

    bool is_first_symbol = true;

    while ((*it_).get(symbol)) {
      if (delimeter_.find(symbol) != std::string::npos) {
        break;
      }
      is_first_symbol = false;
      substr_ += symbol;
    }
  }
};