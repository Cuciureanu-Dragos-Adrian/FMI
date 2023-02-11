import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'colon'
})
export class ColonPipe implements PipeTransform {

  transform(value: unknown, ...args: unknown[]): unknown {
    return value + ':';
  }

}
