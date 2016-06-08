object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = #1043#1077#1085#1077#1090#1080#1095#1077#1089#1082#1080#1081' '#1072#1083#1075#1086#1088#1080#1090#1084
  ClientHeight = 524
  ClientWidth = 476
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 470
    Height = 86
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 484
    object Label1: TLabel
      Left = 16
      Top = 19
      Width = 29
      Height = 13
      Caption = #1042#1074#1086#1076':'
    end
    object Label2: TLabel
      Left = 202
      Top = 43
      Width = 96
      Height = 13
      Caption = #1050#1086#1083'-'#1074#1086' '#1087#1086#1082#1086#1083#1077#1085#1080#1081':'
    end
    object Label3: TLabel
      Left = 16
      Top = 48
      Width = 70
      Height = 13
      Caption = #1052#1091#1090#1072#1094#1080#1103' (%):'
    end
    object Label4: TLabel
      Left = 142
      Top = 48
      Width = 24
      Height = 13
      Caption = '* 0.1'
    end
    object edtInput: TEdit
      Left = 64
      Top = 16
      Width = 305
      Height = 21
      TabOrder = 0
      OnKeyUp = edtInputKeyUp
    end
    object btnEnter: TButton
      Left = 383
      Top = 14
      Width = 70
      Height = 49
      Caption = #1042#1074#1086#1076
      TabOrder = 1
      OnClick = btnEnterClick
    end
    object stResult: TStaticText
      Left = 304
      Top = 46
      Width = 65
      Height = 17
      AutoSize = False
      BorderStyle = sbsSingle
      TabOrder = 2
    end
    object edtMut: TEdit
      Left = 102
      Top = 43
      Width = 35
      Height = 21
      NumbersOnly = True
      TabOrder = 3
      Text = '30'
      OnKeyUp = edtMutKeyUp
    end
  end
  object GroupBox1: TGroupBox
    AlignWithMargins = True
    Left = 3
    Top = 95
    Width = 470
    Height = 426
    Align = alClient
    Caption = #1055#1086#1082#1086#1083#1077#1085#1080#1103
    TabOrder = 1
    ExplicitTop = 122
    ExplicitWidth = 559
    ExplicitHeight = 399
    object mmText: TMemo
      Left = 2
      Top = 15
      Width = 466
      Height = 409
      Align = alClient
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
      ExplicitWidth = 555
      ExplicitHeight = 382
    end
  end
end
