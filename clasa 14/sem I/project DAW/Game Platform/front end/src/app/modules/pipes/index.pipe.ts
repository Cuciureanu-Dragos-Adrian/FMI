import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'index'
})
export class IndexPipe implements PipeTransform {

  transform(value: unknown, ...args: unknown[]): unknown {
    return value + '.';
  }

}
