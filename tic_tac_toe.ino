int board[3][3] = { };


int diode_states[3][3] = {};

int buttons[3][3] = {
  {9,10,11},
  {12,A4,A0},
  {A1,A2,A3}
};

int turn = 1;
bool game_ended = false;

void setup()
{
  for(int i = 0;i<9;i++){
  	pinMode(i,OUTPUT);
  }
  
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){
  		pinMode(buttons[i][j],INPUT_PULLUP);
    }
  }
  
}

void loop()
{
  if(!game_ended){
    get_buttons();
    status();
    if(check_winners())game_ended = true;
  }else{
  	//display wiener
	display_winner();
  }
    
  lightBoard();
}

void display_winner(){
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){ 
      if(check_winners() == 1){
        digitalWrite(3+i,HIGH);
        digitalWrite(6+i,LOW);
      }else if(check_winners() == 2){
        digitalWrite(3+i,LOW);
        digitalWrite(6+i,HIGH);
      }
      
      digitalWrite(j,LOW);
      delay(50);
      digitalWrite(j,HIGH);
     
    }
    digitalWrite(3+i,LOW);
    digitalWrite(6+i,LOW);
  }
}

int check_winners(){
  int winner = 0;
  //check rows
  if(board[0][0] == board[0][1] && board[0][1] == board[0][2])
    winner = board[0][0];
  else if(board[1][0] == board[1][1] && board[1][1] == board[1][2])
    winner = board[1][0];
  else if(board[2][0] == board[2][1] && board[2][1] == board[2][2])
    winner = board[2][0];
    
  //check cols
  if(board[0][0] == board[1][0] && board[1][0] == board[2][0])
    winner = board[0][0];
  else if(board[0][1] == board[1][1] && board[1][1] == board[2][1])
    winner = board[0][1];
  else if(board[0][2] == board[1][2] && board[1][2] == board[2][2])
    winner = board[0][2];
    
  //check diagonals
  if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    winner = board[0][0];
  else if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
    winner = board[0][2];
    
  return winner;
}

void get_buttons(){
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){
      if(digitalRead(buttons[i][j])!=1 && board[i][j]==0){
      	board[i][j] = turn;
        turn = turn == 1 ? 2 : 1;
      }
    }
  }
}

void status(){
  for(int i = 0;i<3;i++){
    for(int j = 0;j<3;j++){
      if(board[i][j]!=0){
        diode_states[i][j] = LOW;
      }else{
        diode_states[i][j] = HIGH;
      }
    }
  }
}


void lightBoard(){
  for(int i = 0;i<3;i++){

    for(int j = 0;j<3;j++){ 
      
      if(board[i][j] == 1){
        digitalWrite(3+i,HIGH);
        digitalWrite(6+i,LOW);
      }else if(board[i][j] == 2){
        digitalWrite(3+i,LOW);
        digitalWrite(6+i,HIGH);
      }
      
      int cathode = diode_states[i][j];
      
      digitalWrite(j,cathode);  
      
      delay(2.5);
     
      if(cathode==LOW){
        digitalWrite(j,HIGH);
      }
      
    }
    digitalWrite(3+i,LOW);
    digitalWrite(6+i,LOW);
  }
}
