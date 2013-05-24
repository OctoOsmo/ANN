object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = #1040#1074#1090#1086#1072#1089#1089#1086#1094#1080#1072#1090#1080#1074#1085#1072#1103' '#1089#1077#1090#1100
  ClientHeight = 242
  ClientWidth = 527
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LabelNeuronCount: TLabel
    Left = 8
    Top = 48
    Width = 199
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1085#1077#1081#1088#1086#1085#1086#1074' '#1089#1082#1088#1099#1090#1086#1075#1086' '#1089#1083#1086#1103' ='
  end
  object TrackBarNeuronCount: TTrackBar
    Tag = 1
    Left = 0
    Top = 0
    Width = 527
    Height = 33
    Align = alTop
    ParentShowHint = False
    Position = 4
    ShowHint = False
    TabOrder = 0
    OnChange = TrackBarNeuronCountChange
  end
  object Button2: TButton
    Left = 384
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 1
    OnClick = Button2Click
  end
  object OpenInputDialog: TOpenDialog
    FileName = 'in.txt'
    Filter = 'txt|*.txt'
    InitialDir = '.\'
    Left = 96
    Top = 80
  end
  object MainMenu: TMainMenu
    Left = 24
    Top = 152
    object NFile: TMenuItem
      Caption = #1060#1072#1081#1083
      object NOpen: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
        OnClick = NOpenClick
      end
      object NOpenWeights: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1074#1077#1089#1072
      end
      object NSaveWeights: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074#1077#1089#1072
        OnClick = NSaveWeightsClick
      end
      object NSaveMatrix: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074#1099#1093#1086#1076' '#1089#1077#1090#1080
        OnClick = NSaveMatrixClick
      end
      object NExit: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = NExitClick
      end
    end
  end
  object SaveWeightsDialog: TSaveDialog
    FileName = 'w.txt'
    Filter = 'txt|*.txt'
    InitialDir = '.\'
    Left = 232
    Top = 96
  end
  object SaveMatrixDialog: TSaveDialog
    FileName = 'xout.txt'
    Filter = 'txt|*.txt'
    InitialDir = '.'
    Left = 336
    Top = 112
  end
end
