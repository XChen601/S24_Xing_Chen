#pragma once

class Player {
public:
    Player(int gameRows, int startRow = 2);
    void MoveUp();
    void MoveDown();
    int GetCurrentRow() const;

private:
    int gameRows;
    int currentRow;
};