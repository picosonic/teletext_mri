\ Fill Mode 7 screen
INCLUDE "os.asm"

srca = &60
srcb = &62
srcc = &64
srcd = &66

desta = &70
destb = &72
destc = &74
destd = &76

frame = &78

ORG &2000

.start
  ; Mode 7
  LDA #&16:JSR OSWRCH
  LDA #&07:JSR OSWRCH

  ; Hide the cursor
  LDA #23:JSR OSWRCH
  LDA #01:JSR OSWRCH
  LDA #00:JSR OSWRCH
  JSR OSWRCH:JSR OSWRCH:JSR OSWRCH:JSR OSWRCH:JSR OSWRCH:JSR OSWRCH:JSR OSWRCH

  ; Set up source frame
  LDA #&00:STA frame

  ; Set up source offsets
  LDA #(frames) MOD 256:STA srca
  LDA #(frames) DIV 256:STA srca+1

  LDA #(frames+&100) MOD 256:STA srcb
  LDA #(frames+&100) DIV 256:STA srcb+1

  LDA #(frames+&200) MOD 256:STA srcc
  LDA #(frames+&200) DIV 256:STA srcc+1

  LDA #(frames+&300) MOD 256:STA srcd
  LDA #(frames+&300) DIV 256:STA srcd+1

  ; Set up screen offsets
  LDA #(MODE7BASE) MOD 256:STA desta
  LDA #(MODE7BASE) DIV 256:STA desta+1

  LDA #(MODE7BASE+&100) MOD 256:STA destb
  LDA #(MODE7BASE+&100) DIV 256:STA destb+1

  LDA #(MODE7BASE+&200) MOD 256:STA destc
  LDA #(MODE7BASE+&200) DIV 256:STA destc+1

  LDA #(MODE7BASE+&300) MOD 256:STA destd
  LDA #(MODE7BASE+&300) DIV 256:STA destd+1

.main

  ; Copy frame from source to dest
  LDY #&00
.pageloop
  LDA (srca),Y:STA (desta),Y
  LDA (srcb),Y:STA (destb),Y
  LDA (srcc),Y:STA (destc),Y
  LDA (srcd),Y:STA (destd),Y
  INY
  BNE pageloop

  ; Move on to next frame
  INC frame:LDA frame
  CMP #22
  BNE nextpage
  LDA #&00:STA frame ; Reset to first frame
.nextpage

  LDA #(frames) DIV 256:STA srca+1 ; Load frames base address

  LDA frame
  ASL A:ASL A ; * 4
  CLC
  ADC srca+1
  STA srca+1

  TAX
  INX:STX srcb+1
  INX:STX srcc+1
  INX:STX srcd+1

.delay
{
  LDY &00
.yloop
  LDX &E0
.xloop
  INX
  BNE xloop
  INY
  BNE yloop
}

  JMP main
 
.finished
  RTS

  ALIGN &100
.frames
  INCBIN "txmri"

.end

SAVE "Main", start, end
