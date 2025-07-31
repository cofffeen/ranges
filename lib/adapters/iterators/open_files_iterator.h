#pragma once

#include <fstream>

template <typename Adapter> 
class OpenFilesIterator {
public:
  using iterator = Adapter::iterator;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::input_iterator_tag;
  using value_type = std::ifstream;
  using reference = std::ifstream &;

  OpenFilesIterator(const iterator &begin, const iterator &end)
      : it_(begin), begin_(begin), end_(end),
        fin_(std::make_shared<std::ifstream>()) {
    OpenFile();
  }

  OpenFilesIterator(const OpenFilesIterator &other)
      : it_(other.it_), begin_(other.begin_), end_(other.end_),
        fin_(other.fin_) {}

  ~OpenFilesIterator() = default;

  OpenFilesIterator &operator=(const OpenFilesIterator &other) {
    it_ = other.it_;
    begin_ = other.begin_;
    end_ = other.end_;

    OpenFile();

    return *this;
  }

  reference operator*() const { return *fin_; }

  bool operator==(const OpenFilesIterator &other) const {
    return (it_ == other.it_);
  }

  bool operator!=(const OpenFilesIterator &other) const {
    return !(*this == other);
  }

  OpenFilesIterator &operator++() {
    ++it_;
    OpenFile();
    return *this;
  }

  OpenFilesIterator operator++(int) {
    OpenFilesIterator<Adapter> copy = *this;
    ++(*this);
    return copy;
  }

private:
  iterator begin_;
  iterator end_;
  iterator it_;
  std::shared_ptr<std::ifstream> fin_;

  void OpenFile() {
    for (; it_ != end_; ++it_) {
      if (fin_->is_open()) {
        fin_->close();
      }

      fin_->clear();
      fin_->open((*it_).string());

      if (fin_->is_open()) {
        break;
      }
    }
  }
};