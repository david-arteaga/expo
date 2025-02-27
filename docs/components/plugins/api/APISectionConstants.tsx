import React from 'react';

import { InlineCode } from '~/components/base/code';
import { B, P } from '~/components/base/paragraph';
import { H2, H3Code } from '~/components/plugins/Headings';
import { APIDataType } from '~/components/plugins/api/APIDataType';
import { ConstantDefinitionData } from '~/components/plugins/api/APIDataTypes';
import { APISectionDeprecationNote } from '~/components/plugins/api/APISectionDeprecationNote';
import { APISectionPlatformTags } from '~/components/plugins/api/APISectionPlatformTags';
import {
  CommentTextBlock,
  getTagNamesList,
  STYLES_APIBOX,
} from '~/components/plugins/api/APISectionUtils';

export type APISectionConstantsProps = {
  data: ConstantDefinitionData[];
  apiName?: string;
};

const renderConstant = (
  { name, comment, type }: ConstantDefinitionData,
  apiName?: string
): JSX.Element => (
  <div key={`constant-definition-${name}`} css={STYLES_APIBOX}>
    <APISectionDeprecationNote comment={comment} />
    <APISectionPlatformTags comment={comment} prefix="Only for:" firstElement />
    <H3Code tags={getTagNamesList(comment)}>
      <InlineCode>
        {apiName ? `${apiName}.` : ''}
        {name}
      </InlineCode>
    </H3Code>
    {type && (
      <P>
        <B>Type:</B> <APIDataType typeDefinition={type} />
      </P>
    )}
    <CommentTextBlock comment={comment} includePlatforms={false} />
  </div>
);

const APISectionConstants = ({ data, apiName }: APISectionConstantsProps) =>
  data?.length ? (
    <>
      <H2 key="constants-header">Constants</H2>
      {data.map(constant => renderConstant(constant, apiName))}
    </>
  ) : null;

export default APISectionConstants;
