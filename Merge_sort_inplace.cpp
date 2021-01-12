template <typename InputItLeft, typename InputItRight, typename OutputIt, typename Compare>
OutputIt Merge(InputItLeft left_first, InputItLeft left_last, InputItRight right_first,
               InputItRight right_last, OutputIt out_first, Compare comp) {
    for (; left_first != left_last; ++out_first) {
        if (right_first == right_last) {
            for (; left_first != left_last; ++left_first, ++out_first) {
                std::swap(*out_first, *left_first);
            }
            return out_first;
        }
        if (comp(*right_first, *left_first)) {
            std::swap(*out_first, *right_first);
            ++right_first;
        } else {
            std::swap(*out_first, *left_first);
            ++left_first;
        }
    }

    for (; right_first != right_last; ++right_first, ++out_first) {
        std::swap(*out_first, *right_first);
    }
    return out_first;
}

template <typename RandomIt, typename Compare = std::less<>>
void MergeSortImpl(RandomIt first, RandomIt last, RandomIt buffer, Compare comp = {}) {
    int block_size = 1;
    int size = std::distance(first, last);
    while (block_size < size) {
        auto middle_iter = std::next(first, block_size);
        auto buffer_iter = buffer;
        int elements_remained = size - block_size;
        do {
            auto first_of_left_segment = std::prev(middle_iter, block_size);
            auto last_of_right_segment = std::next(middle_iter,
                                                   std::min(block_size, elements_remained));
            Merge(first_of_left_segment, middle_iter, middle_iter,
                  last_of_right_segment, buffer_iter, comp);

            while (first_of_left_segment != last_of_right_segment) {

                std::swap(*first_of_left_segment, *buffer_iter);
                ++buffer_iter;
                ++first_of_left_segment;
            }

            std::advance(middle_iter, std::min(2 * block_size, elements_remained));
            elements_remained -= 2 * block_size;
        } while (middle_iter != last);
        
        block_size *= 2;
    }
}

template <typename RandomIt, typename Compare = std::less<>>
void MergeSort(RandomIt first, RandomIt last, Compare comp = {}) {
    // works in-place
    if (first == last) {
        return;
    }

    int size = std::distance(first, last);
    int block_size = size / 4;
    int sorted = size / 2;
    MergeSortImpl(std::next(first, (size + 1) / 2), last, first, comp);

    while (sorted < size - 1) {
        auto left_last = std::next(first, block_size);
        auto buffer = std::next(first, size - sorted - block_size);
        MergeSortImpl(first, left_last, buffer, comp);
        Merge(first, left_last, std::next(first, size - sorted), last, buffer, comp);
        sorted += block_size;
        block_size = (size - sorted) / 2;
    }

    while (std::next(first) != last) {
        if (comp(*std::next(first), *first)) {
            std::swap(*std::next(first), *first);
        }
        ++first;
    }
}
