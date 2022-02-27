def getCols(board_, row=0, col=0):
    return set(board_[row])

def getRows(board_, row=0, col=0):
    return set([x[col] for x in board_])

def getSquare(board_, row=0, col=0):
    rRange = range((row//3) * 3, ((row//3) + 1) * 3)
    cRange = range((col//3) * 3, ((col//3) + 1) * 3)
    rows = [board_[r] for r in rRange]
    return set([r[c] for r in rows for c in cRange])

def show(board_):
    for rows in board_:
        for col in rows:
            print(col, end=" ")
        print()

def predict(board):
    for row in range(9):
        for col in range(9):
            val = board[row][col]
            # 지금 나는 올바른 상태이다 (0이 아닌경우는 정답으로 확정)
            if val != 0: continue
            cols = getCols(board, row, col)
            rows = getRows(board, row, col)
            square = getSquare(board, row, col)
            candidated = {1,2,3,4,5,6,7,8,9} - cols - rows - square
            # 지금 후보군이 없다 = 내가 잘못됐다.
            if len(candidated) == 0:
                return False
            for pVal in candidated:
                preVal = board[row][col]
                board[row][col] = pVal
                isSuccess = predict(board)
                if isSuccess:
                    return isSuccess
                board[row][col] = preVal
            # 내 자식이 모두 잘못됐다 = 내가 잘못됐다
            return False
    return True
    
def read():
    return [[int(x) for x in input().split()] for _ in range(9)]

def main():
    board = read()
    predict(board)
    show(board)

if __name__ == "__main__":
    main()