
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejeong <sejeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:53:27 by sejeong           #+#    #+#             */
/*   Updated: 2021/04/04 20:41:54 by sejeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
​
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
​
int        g_set_row[5][5];
int        g_set_col[5][5];
​
int        check_argv(char* str, int data[])
{
    int        word_count;
    int        i;
​
    word_count = 0;
    i = 0;
    while (word_count < 16 && str[i] != '\0')
    {
        if (i % 2 == 0)
        {
            if (str[i] < '0' || str[i] > '4')
                return (1);
            else
            {
                *data++ = str[i] - '0';
                word_count++;
            }
        }
        else if (str[i] != ' ' && str[i] < 9 && str[i] > 13)
            return (1);
        i++;
    }
    if (word_count == 16 && i == 31)
        return (0);
    else
        return (1);
}
​
int        check(int argc, char** argv, int *data)
{
    char* str;
​
    if (argc != 2)
        return (1);
    str = argv[1];
    if (check_argv(str, data))
        return (1);
    return (0);
}
​
int        valid_down(int (*board)[5], int *data)
{
    int        i;
    int        j;
    int        cnt;
    int        line_max;
​
    i = 0;
    while (++i < 5)
    {
        cnt = 0;
        line_max = 0;
        j = 0;
        while (++j < 5)
        {
            if (line_max < board[j][i])
            {
                line_max = board[j][i];
                cnt++;
            }
        }
        if (cnt != data[i - 1] && data[i - 1] != 0)
            return (0);
    }
    return (1);
}
​
int        valid_up(int (*board)[5], int *data)
{
    int        i;
    int        j;
    int        cnt;
    int        line_max;
​
    i = 0;
    while (++i < 5)
    {
        cnt = 0;
        line_max = 0;
        j = 0;
        while (++j < 5)
        {
            if (line_max < board[5 - j][i])
            {
                line_max = board[5 - j][i];
                cnt++;
            }
        }
        if (cnt != data[i + 3] && data[i + 3] != 0)
            return (0);
    }
    return (1);
}
​
int        valid_right(int (*board)[5], int *data)
{
    int        i;
    int        j;
    int        cnt;
    int        line_max;
​
    i = 0;
    while (++i < 5)
    {
        cnt = 0;
        line_max = 0;
        j = 0;
        while (++j < 5)
        {
            if (line_max < board[i][j])
            {
                line_max = board[i][j];
                cnt++;
            }
        }
        if (cnt != data[i + 7] && data[i + 7] != 0)
            return (0);
    }
    return (1);
}
​
int        valid_left(int (*board)[5], int *data)
{
    int        i;
    int        j;
    int        cnt;
    int        line_max;
​
    i = 0;
    while (++i < 5)
    {
        cnt = 0;
        line_max = 0;
        j = 0;
        while (++j < 5)
        {
            if (line_max < board[i][5 - j])
            {
                line_max = board[i][5 - j];
                cnt++;
            }
        }
        if (cnt != data[i + 11] && data[i + 11] != 0)
            return (0);
    }
    return (1);
}
​
int        is_valid(int (*board)[5], int* data)
{
    if (!valid_down(board, data))
        return (0);
    if (!valid_up(board, data))
        return (0);
    if (!valid_right(board, data))
        return (0);
    if (!valid_left(board, data))
        return (0);
    return (1);
}
​
void    set_board(int (*board)[5], int row, int column, int num)
{
    board[row][column] = num;
    g_set_row[row][num] = 1;
    g_set_col[column][num] = 1;
}
​
void    unset(int row, int column, int num)
{
    g_set_row[row][num] = 0;
    g_set_col[column][num] = 0;
}
​
int        helper(int (*board)[5], int row, int column, int* data)
{
    int        nextNum;
​
    if (row == 5 && is_valid(board, data))
        return (1);
    else if (row == 5)
        return (0);
    if (column == 5)
        return (helper(board, row + 1, 1, data));
    nextNum = 0;
    while (++nextNum < 5)
    {
        if (g_set_row[row][nextNum] || g_set_col[column][nextNum])
            continue;
        set_board(board, row, column, nextNum);
        if (helper(board, row, column + 1, data))
            return (1);
        unset(row, column, nextNum);
    }
    return (0);
}
​
void    init_set(void)
{
    int        i;
    int        j;
​
    i = 0;
    while (++i < 5)
    {
        j = 0;
        while (++j < 5)
        {
            g_set_row[i][j] = 0;
            g_set_col[i][j] = 0;
        }
    }
}
​
void    print(int (*board)[5])
{
    int        i;
    int        j;
​
    i = 0;
    while (++i < 5)
    {
        j = 0;
        while (++j < 5)
        {
            board[i][j] += '0';
            write(1, &board[i][j] , 1);
            if (j == 4)
                write(1, "\n", 1);
            else
                write(1, " ", 1);
        }
    }
}
​
int        main(int argc, char** argv)
{
    int        data[16];
    int        board[5][5];
​
    if (check(argc, argv, data))
    {
        write(1, "Error\n", 6);
        return (0);
    }
    init_set();
    if (helper(board, 1, 1, data))
    {
        print(board);
    }
    else
        write(1, "Error\n", 6);
}
