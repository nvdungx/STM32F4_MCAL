# script to gen Qt python src from ui design file

Write-Host "Start generating ..."

# get all .ui file
$file_list = Get-ChildItem *.ui -Path "./"

foreach ($item in $file_list)
{
  # corresponding python code file for each ui
  $output_file = "./src/"+$item.BaseName+".py"
  # generate
  pyside6-uic $item.FullName -o $output_file

  $line = [System.Collections.ArrayList]::new()
  # regex find windowui.resize line
  [regex]$reg1 = '^.*\.resize\(\d+,\s\d+\)'
  # regex find icons/path line
  [regex]$reg2 = '^.*(u"icons.*").*'
  
  # get each line of file and append to $line list
  Get-Content $output_file | %{
    if (([regex]('^class .*\(object\):')).IsMatch($_.ToString())) {
      [void]$line.Add('import os')
      [void]$line.Add($_.ToString())
    }
    elseif ($reg1.Match($_.ToString()).Success) {
      [void]$line.Add($_.ToString())
      # append curent directory var
      [void]$line.Add('        application_path = os.path.dirname(__file__)')
      [void]$line.Add('        self.uidir = os.path.abspath(os.path.join(application_path, "../."))')
    }
    elseif ($reg2.Match($_.ToString()).Success) {
      # replace current icon path with new one
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