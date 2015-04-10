/*
:: :: DESCRIPTION ::
This is C source for small musical pentatonic toy-program for Linux that I wrote.
This program has C major, G major, Eb major and E minor pentatonic scales.
You can play them right from keyboard (12345, QWERT, ASDFG, ZXCVB).
Save this text as pentatonic.c file, navigate with terminal and...
...compile with: gcc -o pentatonic pentatonic.c; then run with ./pentatonic
Tested on Ubuntu 13.04 Alpha with gcc/g++ (Ubuntu/Linaro 4.7.2-19ubuntu1)
NOTE 1. It does need Sox to work, since command "play" is used.
NOTE 2. The code is in work for now. It is not final version.
NOTE 3. I am totally newbie in C, so there might be many other
possibilities of replicating my work in other, more correct and easy way.
Created 4 feb 2013 by Security XIII at Gmail Dot Com --- Improved alot in april 2015
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
 
/*
  // Seems that we don't need the following libs
  #include <time.h>
  #include <unistd.h>
  #include <sys/types.h>
*/
 
// These are arrays for pentatonic scales and also a duration array
int array1[]={262,294,330,392,440}; // C major pentatonic scale (C D E G A)
int array2[]={392,440,494,587,659}; // G major pentatonic scale (G A B D E)
int array3[]={277,349,392,466,523}; // Eb major pentatonic scale (Eb F G Bb C)
int array4[]={277,392,440,494,587}; // E minor pentatonic scale
//int darray[]={100,150,200,250,300}; // Duration Array
//char selwf;
char *waveform[] = {"sine", "square", "triangle", "sawtooth", "trapetz", "exp", "whitenoise", "pinknoise", "brownnoise"};
int rrna[]={262,294,330,392,440,392,440,494,587,659,277,349,392,466,523,277,392,440,494,587};
float delays[] = {0.1f, 0.2f, 0.3f, 0.5f, 0.75f, 1.00f};
// waveform id
int wid = 1;
int did = 1;
float dar = 0.1f;
// This is for random generating if you would like to implement it. Not used here.
//max = 5;
int rnd( int max ) {return (rand() % max);} 
// Duration is yet not used (set up to default 0.2 == 200 msec)
int fork_n_execute(int frequency, int wid, float dar)
{
  int status;
  pid_t pid;
  pid = fork ();
 
  if(pid == 0)
  {
  char str[80];
  sprintf(str, "play -q -n synth %f %s %i", dar, waveform[wid], frequency);
  system(str);
  exit(EXIT_SUCCESS);
  }
  return status;
}
 
int main(int argc, char *argv[])
{
 
  while (1) {
  int key = getkey();
  //int dar = darray[rnd(5)];
  //int del = darray[rnd(5)]*1000;
  //int dar = 200;
  //int dar = 1;
  int del = 100000;
  //int key2 = getkey();
  //echo key;
  //printf(key);
  switch ( key ) {
        case 0x38: {if (did == 0) {dar = delays[did]; printf("Delay is already lowest: %f\n", dar);}
                        else if (did <= 5) {did = did - 1; dar = delays[did]; printf("Lowering delay to %f\n", dar);}}; break;
        case 0x39: {if (did == 5) {dar = delays[did]; printf("Delay is already highest: %f\n", dar);}
                        else if (did < 5) {did = did + 1; dar = delays[did]; printf("Setting delay higher to %f\n", dar);}}; break;
      //case 0x38: {printf("Key 8 pressed. Shorter sound."); del = del - 50000; printf("del is");}; break;
//	case 0x39: {printf("Key 9 pressed. Longer sound."); del = del + 50000; printf("del2");}; break;
        case 0x20: {if (wid == 8) {wid = 0; printf("Setting playmode to %s (%i)\n", waveform[wid], wid);}
			else if (wid < 8) {wid = wid + 1; printf("Setting playmode to %s (%i)\n", waveform[wid], wid);}}; break;
	case 0x37: {printf("Today random number is: %i\n", rnd(5));}; break;
        case 0x6d: {printf("Total random key pressed.\n"); fork_n_execute(rrna[rnd(20)],wid,dar);usleep(del);}; break;
        case 0x1B: {printf("Exit key (ESC) pressed, BB, CU!\n");exit (1);}; break;
     
        case 0x31: {printf("Key 1 Tone C Freq 262 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[0],wid,dar);usleep(del);}; break;
        case 0x32: {printf("Key 2 Tone D Freq 294 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[1],wid,dar);usleep(del);}; break;
        case 0x33: {printf("Key 3 Tone E Freq 330 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[2],wid,dar);usleep(del);}; break;
        case 0x34: {printf("Key 4 Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[3],wid,dar);usleep(del);}; break;
        case 0x35: {printf("Key 5 Tone A Freq 440 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[4],wid,dar);usleep(del);}; break;
        case 0x36: {printf("Random scale 1 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[rnd(5)],wid,dar);usleep(del);}; break;
     
        case 0x71: {printf("Key Q Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[0],wid,dar);usleep(del);}; break;
        case 0x77: {printf("Key W Tone A Freq 440 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[1],wid,dar);usleep(del);}; break;
        case 0x65: {printf("Key E Tone B Freq 494 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[2],wid,dar);usleep(del);}; break;
        case 0x72: {printf("Key R Tone D Freq 587 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[3],wid,dar);usleep(del);}; break;
        case 0x74: {printf("Key T Tone E Freq 659 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[4],wid,dar);usleep(del);}; break;
        case 0x79: {printf("Random scale 2 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[rnd(5)],wid,dar);usleep(del);}; break;

        case 0x61: {printf("Key A Tone Eb Freq 277 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[0],wid,dar);usleep(del);}; break;
        case 0x73: {printf("Key S Tone F Freq 349 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[1],wid,dar);usleep(del);}; break;
        case 0x64: {printf("Key D Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[2],wid,dar);usleep(del);}; break;
        case 0x66: {printf("Key F Tone Bb Freq 466 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[3],wid,dar);usleep(del);}; break;
        case 0x67: {printf("Key G Tone C Freq 523 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[4],wid,dar);usleep(del);}; break;
        case 0x68: {printf("Random scale 3 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[rnd(5)],wid,dar);usleep(del);}; break;

        case 0x7a: {printf("Key Z Tone Eb Freq 277 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[0],wid,dar);usleep(del);}; break;
        case 0x78: {printf("Key X Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[1],wid,dar);usleep(del);}; break;
        case 0x63: {printf("Key C Tone A Freq 440 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[2],wid,dar);usleep(del);}; break;
        case 0x76: {printf("Key V Tone B Freq 494 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[3],wid,dar);usleep(del);}; break;
        case 0x62: {printf("Key B Tone D Freq 587 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[4],wid,dar);usleep(del);}; break;
        case 0x6e: {printf("Random scale 4 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[rnd(5)],wid,dar);usleep(del);}; break;
	    //default: ; break;
  }
  }
  return 0;
}
 
// Function to parse keypresses. Probably a good place to improve.
 
    int getkey() {
        int character;
        struct termios orig_term_attr;
        struct termios new_term_attr;
        tcgetattr(fileno(stdin), &orig_term_attr);
        memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
        new_term_attr.c_lflag &= ~(ECHO|ICANON);
        new_term_attr.c_cc[VTIME] = 0;
        new_term_attr.c_cc[VMIN] = 0;
        tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);
        character = fgetc(stdin);
        tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
        return character;
    }
