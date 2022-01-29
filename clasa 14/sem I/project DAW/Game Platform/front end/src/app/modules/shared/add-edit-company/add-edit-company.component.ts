import { Component, Inject, OnInit } from '@angular/core';
import { AbstractControl, FormControl, FormGroup } from '@angular/forms';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { CompaniesService } from 'src/app/services/companies.service';

@Component({
  selector: 'app-add-edit-company',
  templateUrl: './add-edit-company.component.html',
  styleUrls: ['./add-edit-company.component.scss']
})
export class AddEditCompanyComponent implements OnInit {

  public companyForm: FormGroup = new FormGroup(
    {
    id: new FormControl(''), 
    name: new FormControl(''),
    }
  );
  public title : any;
  public buttonTitle : any;

  constructor(
    @Inject(MAT_DIALOG_DATA) public data : any,
    private companiesService: CompaniesService,
    public dialogRef: MatDialogRef<AddEditCompanyComponent>, 
  ) { 
    if(data.company){
      this.title = 'Edit Company';
      this.buttonTitle = "Edit";
      this.companyForm.patchValue(this.data.company);
    }
    else{
      this.title = 'Add company';
      this.buttonTitle = "Add";
    }
  }

  //getters
  get id(): AbstractControl
  {
    return this.companyForm.get('id')!;
  }

  get name(): AbstractControl
  {
    return this.companyForm.get('name')!;
  }

  ngOnInit(): void {
  }

  public addCompany(): void{
    if(this.buttonTitle == "Add")
    {
      this.companiesService.addCompany(this.companyForm.value).subscribe({
        next:(result : any) => {
          this.dialogRef.close(result);
        },
        error:(error : any) => {
          console.error(error);
        },
      });
    }
    else
    {
      this.companiesService.editCompany(this.companyForm.value).subscribe({
        next:(result : any) => {
          this.dialogRef.close(result);
        },
        error:(error : any) => {
          console.error(error);
        },
      });
    }
  }

}
