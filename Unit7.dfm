object Form7: TForm7
  Left = 0
  Top = 0
  Caption = 'MiniCalculate v1.0'
  ClientHeight = 518
  ClientWidth = 926
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 24
    Top = 24
    Width = 24
    Height = 13
    Caption = #20844#24335
  end
  object lbl2: TLabel
    Left = 480
    Top = 24
    Width = 205
    Height = 13
    Caption = #65288'*'#27880#65289#21442#25968#21517#31216#35831#20351#29992'&&'#26631#24535#21253#35065#36215#26469
  end
  object lbl3: TLabel
    Left = 744
    Top = 48
    Width = 158
    Height = 249
    Caption = #20351#29992#35828#26126#65306#13#10'1.'#23450#20041#20844#24335#13#10'2.'#32763#35793#20844#24335#13#10'3.'#32473#21464#37327#36171#20540#13#10'4.'#35745#31639
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clHighlight
    Font.Height = -27
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object mmo1: TMemo
    Left = 80
    Top = 88
    Width = 185
    Height = 89
    Lines.Strings = (
      'mmo1')
    TabOrder = 0
  end
  object mmo2: TMemo
    Left = 344
    Top = 112
    Width = 185
    Height = 89
    Lines.Strings = (
      'mmo2')
    TabOrder = 1
  end
  object btn_calculate: TBitBtn
    Left = 240
    Top = 224
    Width = 75
    Height = 25
    Caption = #35745#31639
    TabOrder = 2
    OnClick = btn_calculateClick
  end
  object edt1: TEdit
    Left = 64
    Top = 24
    Width = 377
    Height = 21
    TabOrder = 3
    Text = '&et&+|&cd&-&qq&|'
  end
  object flwpnl1: TFlowPanel
    Left = 0
    Top = 352
    Width = 926
    Height = 166
    Align = alBottom
    TabOrder = 4
  end
  object btn1: TBitBtn
    Left = 454
    Top = 232
    Width = 75
    Height = 25
    Caption = #32763#35793#20844#24335
    TabOrder = 5
    OnClick = btn1Click
  end
  object btn2: TBitBtn
    Left = 656
    Top = 232
    Width = 75
    Height = 25
    Caption = #39044#22788#29702
    TabOrder = 6
    OnClick = btn2Click
  end
end
