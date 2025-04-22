#include "queue.h"
#include "linked_list.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    insert_at_head(&q->data, serialize(state));
}

struct game_state dequeue(struct queue *q) { 
    size_t value = remove_from_tail(&q->data);
    return deserialize(value);
}

bool are_states_same(struct game_state state1, struct game_state state2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state1.tiles[i][j] != state2.tiles[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool is_visited(struct linked_list *visited, struct game_state state) {
    struct list_node *current = visited->head;
    struct game_state visited_state;
    while (current != NULL) {
        visited_state = deserialize(current->value);
        if (are_states_same(visited_state, state)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

struct game_state zero_num_steps(struct game_state state) {
    state.num_steps = 0;
    return state;
}

int number_of_moves(struct game_state start) { 
    struct queue q = {0};
    static bool visited[10007];

    enqueue(&q, start);

    visited[serialize(zero_num_steps(start)) % 10007] = true;

    struct game_state solved = {
        .tiles = {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
            {13,14,15,0}
        },
    };

    while (q.data.head != NULL) {
        struct game_state current = dequeue(&q);
        if (are_states_same(current, solved)) {
            free_list(q.data);
            return current.num_steps;
        }
        struct game_state test_state = current;

        move_up(&test_state);
        if (!are_states_same(test_state, current) && !visited[serialize(zero_num_steps(test_state)) % 10007]) {
            enqueue(&q, test_state);
            visited[serialize(zero_num_steps(test_state)) % 10007] = true;
        }

        test_state = current;
        move_down(&test_state);
        if (!are_states_same(test_state, current) && !visited[serialize(zero_num_steps(test_state)) % 10007]) {
            enqueue(&q, test_state);
            visited[serialize(zero_num_steps(test_state)) % 10007] = true;
        }

        test_state = current;
        move_left(&test_state);
        if (!are_states_same(test_state, current) && !visited[serialize(zero_num_steps(test_state)) % 10007]) {
            enqueue(&q, test_state);
            visited[serialize(zero_num_steps(test_state)) % 10007] = true;
        }

        test_state = current;
        move_right(&test_state);
        if (!are_states_same(test_state, current) && !visited[serialize(zero_num_steps(test_state)) % 10007]) {
            enqueue(&q, test_state);
            visited[serialize(zero_num_steps(test_state)) % 10007] = true;
        }
    }
    free_list(q.data);
    return 0; 
}
