# script to gen Qt python src from ui design file

Write-Host "Start generating ..."

$file_list = Get-ChildItem *.ui -Path "./"

foreach ($item in $file_list)
{
  $output_file = "./src/"+$item.BaseName+".py"
  pyside6-uic $item.FullName -o $output_file

  $line = [System.Collections.ArrayList]::new()
  [regex]$reg1 = '^.*\.resize\(\d+,\s\d+\)'
  [regex]$reg2 = '^.*(u"icons.*").*'
  Get-Content $output_file | %{
    if ($_.ToString() -eq 'from PySide6.QtWidgets import *') {
      [void]$line.Add($_.ToString())
      [void]$line.Add('import os')
    }
    elseif ($reg1.Match($_.ToString()).Success) {
      [void]$line.Add($_.ToString())
      [void]$line.Add('        application_path = os.path.dirname(__file__)')
      [void]$line.Add('        self.uidir = os.path.abspath(os.path.join(application_path, "../."))')
    }
    elseif ($reg2.Match($_.ToString()).Success) {
      $temp = $_.ToString().Replace($reg2.Match($_.ToString()).Groups[1].ToString(), ("os.path.join(self.uidir, {0})" -f $reg2.Match($_.ToString()).Groups[1].ToString()))
      [void]$line.Add($temp)
    }
    else{
      [void]$line.Add($_.ToString())
    }
  }
  $content = $line | Out-String
  Set-Content -Path $output_file -Value $content

  Write-Host "Generate" $item.Name "completed"
}