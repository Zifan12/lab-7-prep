#ifndef PACK_H
#define PACK_H

namespace pack_detail {
    template <typename... Args> constexpr int packSize = 0;

    template <typename T, typename... Ts>
    constexpr int packSize<T, Ts...> = 1 + packSize<Ts...>;

    template <int QueryIndex, typename... Args> struct _packIndexToType;
    template <typename T, typename... Ts>
    struct _packIndexToType<0, T, Ts...> {
        using type = T;
    };

    template <int QueryIndex, typename T, typename... Ts>
    struct _packIndexToType<QueryIndex, T, Ts...> {
        using type = typename _packIndexToType<QueryIndex - 1, Ts...>::type;
    };

    template <int QueryIndex, typename... Args>
    using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

    template <int Accumulated, typename QueryType, typename... Args>
    constexpr int _packTypeToIndex = -1;

    template <int Accumulated, typename QueryType, typename... Ts>
    constexpr int _packTypeToIndex<Accumulated, QueryType, QueryType, Ts...> = Accumulated;

    template <int Accumulated, typename QueryType, typename T, typename... Ts>
    constexpr int _packTypeToIndex<Accumulated, QueryType, T, Ts...> = _packTypeToIndex<Accumulated+1, QueryType, Ts...>;

    template <typename QueryType, typename... Args>
    constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;


}
template <typename... Args>

struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>;

    template <int QueryIndex> using type = pack_detail::packIndexToType<QueryIndex, Args...>;
    template <typename QueryType> constexpr static int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif  // PACK_H
