#include <iostream>
#include <vector>

using namespace std;

struct fan {
  int r_pos;
  int c_pos;
  char dir;
};

void Print_Windmills(vector<vector<int>> &v) {
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i].size(); j++)
      cout << v[i][j] << " ";
    cout << endl;
  }
}

bool Solution(const vector<vector<int>> &windmills) {
  for (int i = 0; i < windmills.size(); i++)
    for (int j = 0; j < windmills[i].size(); j++)
      if (windmills[i][j] == 0)
        return false;

  return true;
}

void Toggle_Dir(vector<vector<int>> &windmills, int r, int c, int r_change,
                int c_change, bool turn_on) {
  while (r >= 0 && r < windmills.size() && c >= 0 && c < windmills[r].size()) {
    if (windmills[r][c] != -1) {
      if (turn_on)
        windmills[r][c]++;
      else {
        if (windmills[r][c] > 0)
          windmills[r][c]--;
      }
    }
    r = r + r_change;
    c = c + c_change;
  }
}

char Clockwise(char d) {
  if (d == 'U')
    return 'R';
  if (d == 'R')
    return 'D';
  if (d == 'D')
    return 'L';
  if (d == 'L')
    return 'U';
}

char Counter_Clockwise(char d) {
  if (d == 'U')
    return 'L';
  if (d == 'R')
    return 'U';
  if (d == 'D')
    return 'R';
  if (d == 'L')
    return 'D';
}

char Opposite(char d) {
  if (d == 'U')
    return 'D';
  if (d == 'R')
    return 'L';
  if (d == 'D')
    return 'U';
  if (d == 'L')
    return 'R';
}

void Turn_On(vector<vector<int>> &windmills, int r, int c, int dir) {
  if (dir == 'U')
    Toggle_Dir(windmills, r, c, -1, 0, true);
  if (dir == 'D')
    Toggle_Dir(windmills, r, c, 1, 0, true);
  if (dir == 'L')
    Toggle_Dir(windmills, r, c, 0, -1, true);
  if (dir == 'R')
    Toggle_Dir(windmills, r, c, 0, 1, true);
}

void Turn_Off(vector<vector<int>> &windmills, int r, int c, int dir) {
  if (dir == 'U')
    Toggle_Dir(windmills, r, c, -1, 0, false);
  if (dir == 'D')
    Toggle_Dir(windmills, r, c, 1, 0, false);
  if (dir == 'L')
    Toggle_Dir(windmills, r, c, 0, -1, false);
  if (dir == 'R')
    Toggle_Dir(windmills, r, c, 0, 1, false);
}
int Solve(vector<vector<int>> &windmills, vector<fan> &fan_list, int pos) {
  if (Solution(windmills))
    return 0;
  if (pos == fan_list.size())
    return 1000000;
  // now try turning fan i
  char d = fan_list[pos].dir;
  // first, go in the direction the fan is pointing right now
  Turn_On(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, d);
  int best = 1000000;
  int cur = Solve(windmills, fan_list, pos + 1);
  if (cur < best)
    best = cur;
  // backtrack, turning off the fans we're pointing at now
  Turn_Off(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, d);

  // look clockwise (1 turn cost)
  char clockwise = Clockwise(d);
  Turn_On(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, clockwise);
  cur = 1 + Solve(windmills, fan_list, pos + 1);
  if (cur < best)
    best = cur;
  Turn_Off(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, clockwise);

  // look counter-clockwise (1 turn cost)
  char ccw = Counter_Clockwise(d);
  Turn_On(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, ccw);
  cur = 1 + Solve(windmills, fan_list, pos + 1);
  if (cur < best)
    best = cur;
  Turn_Off(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, ccw);

  // look opposite (2 turn cost)
  char oppo = Opposite(d);
  Turn_On(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, oppo);
  cur = 2 + Solve(windmills, fan_list, pos + 1);
  if (cur < best)
    best = cur;
  Turn_Off(windmills, fan_list[pos].r_pos, fan_list[pos].c_pos, oppo);

  return best;
}

int main() {
  int r, c;
  cin >> r >> c;

  int cur_case = 1;
  while (r > 0) {
    int n;
    cin >> n;

    // windmills[i][j] holds the # of fans blowing on row i, col j
    vector<vector<int>> windmills(r);
    for (int i = 0; i < r; i++) {
      windmills[i].resize(c, 0);
    }

    vector<fan> fan_list(n);
    for (int i = 0; i < n; i++) {
      cin >> fan_list[i].r_pos;
      if (fan_list[i].r_pos < 0 || fan_list[i].r_pos >= r)
        cout << "Illegal row: " << r << endl;
      cin >> fan_list[i].c_pos;
      if (fan_list[i].c_pos < 0 || fan_list[i].c_pos >= c)
        cout << "Illegal col: " << c << endl;
      cin >> fan_list[i].dir;
      windmills[fan_list[i].r_pos][fan_list[i].c_pos] = -1; // means "a fan"
    }

    //    Print_Windmills(windmills);
    int best = Solve(windmills, fan_list, 0);
    if (best != 1000000)
      cout << "Case " << cur_case << ": " << best << endl;
    else
      cout << "Case " << cur_case << ": Impossible" << endl;
    cur_case++;
    cin >> r >> c;
  }
  return 0;
}
